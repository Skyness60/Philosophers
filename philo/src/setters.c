/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:30:27 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 10:31:08 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(bool *to_set, bool value, pthread_mutex_t *mutex)
{
	handle_mutex(mutex, LOCK);
	*to_set = value;
	handle_mutex(mutex, UNLOCK);
}

void	set_long(long *to_set, long value, pthread_mutex_t *mutex)
{
	handle_mutex(mutex, LOCK);
	*to_set = value;
	handle_mutex(mutex, UNLOCK);
}
