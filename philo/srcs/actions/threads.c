/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:55:55 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 14:25:13 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

static void	*monitor(void *global_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) global_ptr;
	mutex_lock(&philo->global->write);
	printf("\033[1m\033[31mdata value : %d\033[0m", philo->global->i_died);
	mutex_unlock(&philo->global->write);
	while (philo->global->i_died == 0)
	{
		mutex_lock(&philo->lock);
		if (philo->global->finish >= philo->global->num_philo)
			philo->global->i_died = 1;
		mutex_unlock(&philo->lock);
	}
	return ((void *)false);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	philo->time_to_die = philo->global->time_to_die + get_time();
}

bool	thread_init(t_global *global)
{
	int			i;
	pthread_t	thread0;

	i = -1;
	global->timer = get_time();
	if (global->meals_nb > 0)
		if (pthread_create(&thread0, NULL, &monitor, &global->philo[0]))
			return (printf("\033[31mTHREAD ERROR\033[0m"), ft_exit(global), true);
	while (++i < global->num_philo)
	{
		if (pthread_create(&global->tid[i], NULL, &routine, &global->philo[i]))
			return (printf("\033[31mTHREAD ERROR\033[0m"), ft_exit(global), true);
		ft_usleep(1);
	}
	i = -1;
	while (++i < global->num_philo)
		if (pthread_join(global->tid[i], NULL))
			return (printf("\033[31mTHREAD JOIN ERROR\033[0m"), \
			ft_exit(global), true);
	return (false);
}
