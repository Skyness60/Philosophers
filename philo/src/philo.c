/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:23:54 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 06:47:17 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

pthread_mutex_t	*init_forks(t_data *data, int len)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len);
	if (!forks)
		return (free_msg("creating forks\n", NULL), NULL);
	add_ptr(data->trash, (void *)forks);
	i = 0;
	while (i < len)
		if (pthread_mutex_init(&forks[i++], NULL))
			return (free_msg("initializing forks\n", NULL), NULL);
	return (forks);
}

static t_philo	*allocate_philo(t_data *data, pthread_mutex_t *forks)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	if (!philo)
		return (free_msg("malloc error\n", NULL), NULL);
	add_ptr(data->trash, (void *)philo);
	return (init_philos(philo, data, forks), philo);
}

static bool	setup_philo(t_data data, char **argv)
{
	pthread_mutex_t	*forks;
	t_philo			*philo;

	if (init_data(&data, argv) == 0)
		return (false);
	if (data.must_eat == 0)
		return (true);
	forks = init_forks(&data, data.n_philo);
	if (!forks)
		return (false);
	philo = allocate_philo(&data, forks);
	if (!philo)
		return (false);
	if (init_simulation(philo, &data) == false)
		return (the_end(data, forks), false);
	return (the_end(data, forks), true);
}

int	main(int argc, char **argv)
{
	t_data			data;

	data.trash = malloc(sizeof(t_garb_c));
	data.trash->ptr_arr = NULL;
	if (argc == 5 || argc == 6)
	{
		if (setup_philo(data, argv) == false)
			return (free_all(data.trash), free(data.trash), 1);
	}
	else
		return (free(data.trash), write(2, \
		"Error: wrong arguments number\n", 31), 1);
	return (free_all(data.trash), free(data.trash), 0);
}
