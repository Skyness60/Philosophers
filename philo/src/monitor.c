/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:57:24 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 11:24:41 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	end_dinning(t_data *data)
{
	if (get_bool(&data->finish, &data->dinner_mtx) == true)
		return (true);
	return (false);
}

static bool	ready(t_data *data)
{
	if (get_long(&data->ready_nb, &data->dinner_mtx) == data->nb_philo)
		return (true);
	return (false);
}

static	bool	is_dead(t_philo *philo)
{
	long	since_last_meal;

	if (get_bool(&philo->dead, &philo->mutex) == true)
		return (false);
	since_last_meal = get_time(false, true) - get_long(\
	&philo->last_meal_time, &philo->mutex);
	if (since_last_meal > philo->data->time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	t_data	*data_ptr;
	int		i;

	data_ptr = (t_data *)data;
	while (!ready(data_ptr))
		;
	while (!end_dinning(data_ptr))
	{
		i = -1;
		while (++i < data_ptr->nb_philo && !end_dinning(data_ptr))
		{
			if (is_dead(data_ptr->philos + i))
			{
				print_action(DEAD, &data_ptr->philos[i]);
				set_bool(&data_ptr->finish, true, &data_ptr->dinner_mtx);
			}
		}
	}
	return (NULL);
}
