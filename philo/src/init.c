/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:47:27 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 01:06:55 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	if (philo->id == philo->data->nb_philo)
	{
		philo->second_fork = &(forks[0].mutex);
		philo->first_fork = &(forks[philo->id - 1].mutex);
	}
	else if (philo->id % 2 == 1)
	{
		philo->first_fork = &(forks[philo->id].mutex);
		philo->second_fork = &(forks[philo->id - 1].mutex);
	}
	else if (philo->id % 2 == 0)
	{
		philo->first_fork = &(forks[philo->id - 1].mutex);
		philo->second_fork = &(forks[philo->id].mutex);
	}
}

static int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philos;
	while (++i < data->nb_philo)
	{
		philo[i].id = i++;
		philo[i].last_meal_time = 0;
		philo[i].eaten_nb = 0;
		philo[i].full = false;
		philo[i].dead = false;
		philo[i].data = data;
		if (handle_mutex(&(philo[i].mutex), INIT) == -1)
			return (-1);
		assign_forks(&(philo[i]), data->forks);
	}
	return (0);
}

static int	init_fork(t_fork *fork, int id)
{
	if (handle_mutex(&(fork->mutex), INIT) == -1);
		return (-1);
	fork->id = id;
	return (0);
}

int	init(t_data *data)
{
	int	i;

	i = -1;
	data->finish = 0;
	data->ready_nb = 0;
	init_garbage_collector(data->trash);
	handle_mutex(&(data->dinner_mtx), INIT);
	handle_mutex(&(data->write_mtx), INIT);
	data->forks = malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (-1);
	add_ptr(data->trash, (void *)data->forks);
	while (++i < data->nb_philo)
	{
		if (init_fork(data->forks + i, i) == -1)
			return (-1);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (-1);
	add_ptr(data->trash, (void *)data->philos);
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}
