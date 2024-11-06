/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:24:06 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 06:34:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	reset_data(t_data *data)
{
	data->n_philo = -1;
	data->t_die = -1;
	data->t_eat = -1;
	data->t_sleep = -1;
	data->must_eat = -1;
}

static bool	assign_data(t_data *data, int i, char *line)
{
	int	nbr;

	nbr = atoi_phil(line);
	if (nbr == -1 || (nbr == 0 && i != 5))
	{
		write(2, "Error: wrong arguments\n", 24);
		return (false);
	}
	if (i == 1)
		data->n_philo = nbr;
	else if (i == 2)
		data->t_die = nbr;
	else if (i == 3)
		data->t_eat = nbr;
	else if (i == 4)
		data->t_sleep = nbr;
	else if (i == 5)
		data->must_eat = nbr;
	return (true);
}

static bool	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->death_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->last_meal_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->num_meals_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&data->finish_meal_mtx, NULL))
		return (false);
	return (true);
}

bool	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	init_garbage_collector(data->trash);
	reset_data(data);
	while (argv[++i])
		if (assign_data(data, i, argv[i]) == false)
			return (false);
	if (data->must_eat != -1)
		data->bool_meals = true;
	else
		data->bool_meals = false;
	data->death = 0;
	data->start = 0;
	data->finish_meal = 0;
	data->create_threads = false;
	if (init_mutex(data) == false)
		return (write(2, "Error: initializing mutex\n", 27), false);
	return (true);
}

void	init_philos(t_philo *p, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		p[i].id = i + 1;
		p[i].l_fork = &forks[i];
		p[i].r_fork = &forks[(i + 1) % data->n_philo];
		p[i].last_meal = 0;
		p[i].num_meals = 0;
		p[i].leave_dinner_table = 0;
		p[i].data = data;
		p[i].write_mtx = &data->write_mtx;
		p[i].death_mtx = &data->death_mtx;
		p[i].last_meal_mtx = &data->last_meal_mtx;
		p[i].num_meals_mtx = &data->num_meals_mtx;
		p[i].finish_meal_mtx = &data->finish_meal_mtx;
	}
}
