/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:24:21 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 05:30:03 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		protect_mutex(LOCK, philo->l_fork);
		write_action(philo, FORK);
		protect_mutex(LOCK, philo->r_fork);
		write_action(philo, FORK);
	}
	else
	{
		protect_mutex(LOCK, philo->r_fork);
		write_action(philo, FORK);
		protect_mutex(LOCK, philo->l_fork);
		write_action(philo, FORK);
	}
}

int	get_death(t_data *data)
{
	int	dead;

	protect_mutex(LOCK, &data->death_mtx);
	dead = data->death;
	protect_mutex(UNLOCK, &data->death_mtx);
	return (dead);
}

void	set_death(t_data *data, int death)
{
	protect_mutex(LOCK, &data->death_mtx);
	data->death = death;
	protect_mutex(UNLOCK, &data->death_mtx);
}

bool	check_bool(t_philo *philo)
{
	if (philo->data->bool_meals == false)
		return (true);
	protect_mutex(LOCK, &philo->data->num_meals_mtx);
	if (philo->num_meals < philo->data->must_eat)
		return (protect_mutex(UNLOCK, &philo->data->num_meals_mtx), true);
	else
		return (protect_mutex(UNLOCK, &philo->data->num_meals_mtx), false);
}
