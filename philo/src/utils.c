/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:36:30 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 13:25:43 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(bool second, bool mls)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (second == 1)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (mls == 1)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else
		return (time.tv_sec * 1e6 + time.tv_usec);
	return (0);
}

void	increment_long_with_mutex(long *dest, pthread_mutex_t *mtx)
{
	handle_mutex(mtx, LOCK);
	(*dest)++;
	handle_mutex(mtx, UNLOCK);
}

void	print_action(t_philo_state state, t_philo *philo)
{
	long	time;

	if (philo->data->finish)
		return ;
	time = get_time(false, true) - philo->data->start_time;
	handle_mutex(&(philo->data->write_mtx), LOCK);
	if (state == EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (state == TAKE_FIRST_FORK)
		printf("%ld %d has taken a first fork\n", time, philo->id);
	else if (state == TAKE_SECOND_FORK)
		printf("%ld %d has taken a second fork\n", time, philo->id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	else if (state == DEAD)
		printf("%ld %d died\n", time, philo->id);
	handle_mutex(&(philo->data->write_mtx), UNLOCK);
}

void	precise_usleep(long time)
{
	long	start;
	long	time_left;

	start = get_time(false, false);
	while (get_time(false, false) - start < time)
	{
		time_left = (time - (get_time(false, false) - start));
		if (time_left < 1000)
			usleep(time_left / 2);
		else
			while (get_time(false, false) - start < time)
				;
	}
}
