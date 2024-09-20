/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:38:37 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 15:05:09 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_exit(t_global *global)
{
	int	i;

	i = -1;
	if (global)
	{
		while (++i < global->num_philo)
		{
			mutex_destroy(&global->forks[i].mutex);
			mutex_destroy(&global->philo[i].state_mutex);
			mutex_destroy(&global->philo[i].last_meal_mutex);
		}
		mutex_destroy(&global->log_mutex);
		clear_data(global);
	}
}
