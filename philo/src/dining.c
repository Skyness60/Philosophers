/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:34:33 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 01:56:48 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*single_philosopher_scenario(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	handle_mutex(&(philo->first_fork), LOCK);
	print_action(philo, TAKE_FIRST_FORK);
	precise_usleep(philo->data->time_to_die * 1e3);
	print_action(philo, DEAD);
	handle_mutex(&(philo->first_fork), UNLOCK);
	return (NULL);
}

void	start_dining(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time(false, true);
	if (data->nb_philo == 1)
	{
		handle_thread(&(data->philos[0].thread), CREATE, \
		single_philosopher_scenario, &(data->philos[0]));
	}
	else
	{
		while (++i < data->nb_philo)
		{
			handle_thread(&(data->philos[i].thread), CREATE, \
			actual_dining, &(data->philos[i]));
		}
		handle_thread(&(data->monitor), CREATE, monitor, data);
		while (--i >= 0)
			handle_thread(&(data->philos[i].thread), JOIN, NULL, NULL);
		refresh_dining(&data->finish, 1, &data->dinner_mtx);
		handle_thread(&(data->monitor), JOIN, NULL, NULL);
	}
}