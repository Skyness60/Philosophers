/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:30:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 01:31:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		handle_mutex(&(data->philos[i].mutex), DESTROY);
	i = -1;
	while (++i < data->nb_philo)
		handle_mutex(&(data->forks[i].mutex), DESTROY);
	handle_mutex(&(data->write_mtx), DESTROY);
	handle_mutex(&(data->dinner_mtx), DESTROY);
}
