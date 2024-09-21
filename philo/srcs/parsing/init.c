/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:14:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 13:21:51 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_alloc(t_global *global)
{
	global->tid = malloc(global->num_philo * sizeof(pthread_t));
	if (!global->tid)
		return (printf("\033[31mError Malloc\n\033[0m"), ft_exit(NULL), true);
	global->forks = malloc(global->num_philo * sizeof(t_mutex));
	if (!global->forks)
		return (printf("\033[31mError Malloc\n\033[0m"), ft_exit(NULL), true);
	global->philo = malloc(global->num_philo * sizeof(t_philo));
	if (!global->philo)
		return (printf("\033[31mError Malloc\n\033[0m"), ft_exit(NULL), true);
	return (false);
}

static bool	init_forks(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->num_philo)
		mutex_init(&global->forks[i], NULL);
	global->philo[0].left_fork = &global->forks[0];
	global->philo[0].right_fork = &global->forks[global->num_philo - 1];
	i = 0;
	while (i < global->num_philo)
	{
		global->philo[i].left_fork = &global->forks[i];
		global->philo[i].left_fork = &global->forks[i - 1];
		i++;
	}
	return (false);
}

static void	init_philos(t_global *global)
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

static bool	init_data(t_global *global, char **av, int ac)
{
	global->num_philo = (int) ft_atoi(av[1]);
	global->time_to_die = (uint64_t) ft_atoi(av[2]);
	global->time_to_eat = (uint64_t) ft_atoi(av[3]);
	global->time_to_sleep = (uint64_t) ft_atoi(av[4]);
	if (ac == 6)
		global->meals_nb = (int) ft_atoi(av[5]);
	else if (ac == 5)
		global->meals_nb = -1;
	if (global->num_philo <= 0 || global->time_to_die < 0 \
	|| global->time_to_eat < 0 || global->time_to_sleep < 0)
		return (printf("%s\n", ERR_INPUT_VALUE), ft_exit(NULL), true);
	global->i_died = 0;
	global->finish = 0;
	mutex_init(&global->write, NULL);
	mutex_init(&global->lock, NULL);
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
	return (init_philos(global), false);
}
