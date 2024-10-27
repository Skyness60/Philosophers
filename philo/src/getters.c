/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:27:19 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 10:29:59 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_bool(bool *to_get, pthread_mutex_t *mutex)
{
	bool	ret;

	ret = false;
	handle_mutex(mutex, LOCK);
	ret = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}

long	get_long(long *to_get, pthread_mutex_t *mutex)
{
	long	ret;

	ret = 0;
	handle_mutex(mutex, LOCK);
	ret = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (ret);
}
