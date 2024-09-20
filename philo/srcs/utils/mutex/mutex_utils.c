/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:54:40 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 12:04:14 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_utils.h"

void	mutex_init(t_mutex *mutex, const t_mutexattr *mutexattr)
{
	pthread_mutex_init(mutex, mutexattr);
}

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}

void	mutex_destroy(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}
