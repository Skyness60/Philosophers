/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:57:24 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 01:58:57 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	ready(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (data->philos[i].eaten_nb < data->nb_meals)
			return (false);
	}
	return (true);
}

void	*monitor(void *data)
{
	t_data	*data_ptr;
	int		i;

	data_ptr = (t_data *)data;
	while (!ready(data))
		;
}