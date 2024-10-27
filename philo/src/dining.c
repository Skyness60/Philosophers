/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:34:33 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 13:26:16 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	thinking(t_philo *philo, t_data *data)
{
	long	time;

	print_action(THINKING, philo);
	if (data->nb_philo % 2 == 1)
	{
		time = data->time_to_eat * 2 - data->time_to_sleep;
		if (time < 0)
			time = 0;
		precise_usleep(time * 1e3);
	}
}

static void	eating(t_philo *philo)
{
	handle_mutex(philo->first_fork, LOCK);
	print_action(TAKE_FIRST_FORK, philo);
	handle_mutex(philo->second_fork, LOCK);
	print_action(TAKE_SECOND_FORK, philo);
	print_action(EATING, philo);
	set_long(&philo->last_meal_time, get_time(false, true), &philo->mutex);
	precise_usleep(philo->data->time_to_eat * 1e3);
	philo->eaten_nb++;
	if (philo->data->nb_meals != -1 && philo->eaten_nb == philo->data->nb_meals)
		set_bool(&philo->full, true, &philo->mutex);
	handle_mutex(philo->first_fork, UNLOCK);
	handle_mutex(philo->second_fork, UNLOCK);
}

static void	*single_philosopher_scenario(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	handle_mutex(philo->first_fork, LOCK);
	print_action(TAKE_FIRST_FORK, philo);
	precise_usleep(philo->data->time_to_die * 1e3);
	print_action(DEAD, philo);
	handle_mutex(philo->first_fork, UNLOCK);
	return (NULL);
}

static void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(&philo->last_meal_time, get_time(false, true), &philo->mutex);
	increment_long_with_mutex(&philo->data->ready_nb, &philo->data->dinner_mtx);
	while (!end_dinning(philo->data))
	{
		if (get_bool(&philo->full, &philo->mutex) == true)
			break ;
		eating(philo);
		set_long(&philo->last_meal_time, get_time(false, true), &philo->mutex);
		print_action(SLEEPING, philo);
		precise_usleep(philo->data->time_to_sleep * 1e3);
		thinking(philo, philo->data);
	}
	return (NULL);
}

void	start_dining(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time(false, true);
	if (data->nb_philo == 1)
	{
		handle_thread(&(data->philos[0].thread), single_philosopher_scenario, \
		&data->philos[0], CREATE);
		handle_thread(&(data->philos[0].thread), NULL, NULL, JOIN);
	}
	else
	{
		while (i < data->nb_philo)
		{
			handle_thread(&(data->philos[i].thread), dining, \
			&data->philos[i], CREATE);
			i++;
		}
		handle_thread(&data->monitor, monitor, data, CREATE);
		while (--i >= 0)
			handle_thread(&data->philos[i].thread, NULL, NULL, JOIN);
		set_bool(&data->finish, 1, &data->dinner_mtx);
		handle_thread(&data->monitor, NULL, NULL, JOIN);
	}
}
