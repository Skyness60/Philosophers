/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:37:49 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 07:08:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	dead_or_alive(t_philo *philo, int i)
{
	protect_mutex(LOCK, &philo->data->finish_meal_mtx);
	if (philo[i].leave_dinner_table == 0)
	{
		protect_mutex(UNLOCK, &philo->data->finish_meal_mtx);
		protect_mutex(LOCK, &philo->data->last_meal_mtx);
		if (philo->data->t_die < (get_time() - philo->data->start)
			- philo[i].last_meal)
		{
			protect_mutex(UNLOCK, &philo->data->last_meal_mtx);
			write_action(&philo[i], DIED);
			set_death(philo->data, 1);
			return (0);
		}
		protect_mutex(UNLOCK, &philo->data->last_meal_mtx);
	}
	else
		protect_mutex(UNLOCK, &philo->data->finish_meal_mtx);
	return (1);
}

static void	*monitor_philosophers(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (get_death(philo->data) == 0)
	{
		i = -1;
		while (++i < philo->data->n_philo)
		{
			if (dead_or_alive(philo, i) == 0)
				return (NULL);
			protect_mutex(LOCK, philo[i].finish_meal_mtx);
			if (philo[i].data->finish_meal == philo->data->n_philo)
				return (protect_mutex(UNLOCK, philo[i].finish_meal_mtx), NULL);
			protect_mutex(UNLOCK, philo[i].finish_meal_mtx);
		}
		usleep(50);
	}
	return (NULL);
}

bool	init_simulation(t_philo *philo, t_data *data)
{
	pthread_t	hawk;
	int			i;
	bool		join;

	i = -1;
	join = false;
	philo->data->start = get_time();
	if (pthread_create(&hawk, NULL, &monitor_philosophers, (void *)philo))
		return (free_msg("breeding hawk\n", philo), false);
	set_philo(philo, data);
	if (data->create_threads == true)
	{
		if (pthread_join(hawk, NULL))
			join = true;
		while (++i < philo->data->n_philo)
			if (pthread_join(philo[i].thread, NULL))
				join = true;
	}
	if (join == true)
		return (false);
	return (true);
}
