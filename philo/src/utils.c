/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:23:34 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 06:37:45 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	write_action(t_philo *philo, t_state action)
{
	const char	*actions[5];

	actions[0] = SLEEPW;
	actions[1] = FORKW;
	actions[2] = EATW;
	actions[3] = THINKW;
	actions[4] = DIEDW;
	protect_mutex(LOCK, &philo->data->write_mtx);
	if (get_death(philo->data) == 0)
		printf("%ld %d %s\n",
			(get_time() - philo->data->start), philo->id, actions[action]);
	protect_mutex(UNLOCK, &philo->data->write_mtx);
}

void	sleepy_time(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(50);
}

int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	the_end(t_data data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data.n_philo)
		protect_mutex(DESTROY, &forks[i]);
	protect_mutex(DESTROY, &data.finish_meal_mtx);
	protect_mutex(DESTROY, &data.num_meals_mtx);
	protect_mutex(DESTROY, &data.last_meal_mtx);
	protect_mutex(DESTROY, &data.death_mtx);
	protect_mutex(DESTROY, &data.write_mtx);
	(void)forks;
}
