/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:14:42 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 13:25:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	handle_mutex(pthread_mutex_t *mutex, t_mutex_action action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (printf("An error occured initializing a mutex\n"), -1);
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (printf("An error occured destroying a mutex\n"), -1);
	}
	else if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (printf("An error occured locking a mutex\n"), -1);
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (printf("An error occured unlocking a mutex\n"), -1);
	}
	return (0);
}

int	handle_thread(pthread_t *thread, void *(*f)(void *), void *arg, \
t_thread_action action)
{
	if (action == CREATE)
	{
		if (pthread_create(thread, NULL, f, arg) != 0)
			return (printf("An error occured creating a thread\n"), -1);
	}
	else if (action == JOIN)
		if (pthread_join(*thread, NULL) != 0)
			return (printf("An error occured joining a thread\n"), -1);
	else if (action == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			return (printf("An error occured detaching a thread\n"), -1);
	}
	return (0);
}
