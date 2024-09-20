/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:14:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 16:10:16 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	alloc(t_global *global)
{
	return (false);
}

bool	init_forks(t_global *global)
{
	return (false);
}

void	init_philos(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->num_philo)
	{
		global->philo[i].global = global;
		global->philo[i].id = i + 1;
		global->philo[i].time_to_die = global->time_to_die;
		global->philo[i].eat_count = 0;
		mutex_init(&global->philo[i].state_mutex, NULL);
		mutex_init(&global->philo[i].last_meal_mutex, NULL);
	}
}

bool	init_data(t_global *global, char **av, int ac)
{
	global->num_philo = (int) ft_atoi(av[1]);
	global->time_to_die = (uint64_t) ft_atoi(av[2]);
	global->time_to_eat = (uint64_t) ft_atoi(av[2]);
	global->time_to_sleep = (uint64_t) ft_atoi(av[2]);
	if (ac == 6)
		global->meals_nb = 
	return (false);
}

bool	init(t_global *global, char **av, int ac)
{
	if (init_data(global, av, ac))
		return (true);
	if (ft_alloc(global))
		return (true);
	if (init_forks(global))
		return (true);
	init_philos(global);
	return (false);
}
