/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:23:42 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 06:40:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	unstarvation(t_philo *philo)
{
	take_forks(philo);
	write_action(philo, EAT);
	protect_mutex(LOCK, &philo->data->last_meal_mtx);
	philo->last_meal = (get_time() - philo->data->start);
	protect_mutex(UNLOCK, &philo->data->last_meal_mtx);
	protect_mutex(LOCK, &philo->data->num_meals_mtx);
	philo->num_meals++;
	protect_mutex(UNLOCK, &philo->data->num_meals_mtx);
	sleepy_time(philo->data->t_eat);
	protect_mutex(UNLOCK, philo->l_fork);
	protect_mutex(UNLOCK, philo->r_fork);
}

static void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(50);
	while (get_death(philo->data) == 0 && check_bool(philo) == true)
	{
		unstarvation(philo);
		if (check_bool(philo) == false)
			return (protect_mutex(LOCK, &philo->data->finish_meal_mtx), \
			philo->data->finish_meal++, philo->leave_dinner_table = 1, \
			protect_mutex(UNLOCK, &philo->data->finish_meal_mtx), NULL);
		write_action(philo, SLEEP);
		sleepy_time(philo->data->t_sleep);
		write_action(philo, THINK);
	}
	return (NULL);
}

static void	*one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (check_bool(philo) == true)
		return (protect_mutex(LOCK, philo->l_fork), write_action(philo, FORK), \
		protect_mutex(UNLOCK, philo->l_fork), sleepy_time(philo->data->t_die), \
		NULL);
	return (NULL);
}

bool	create_threads(t_philo *philo, t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->n_philo)
		if (pthread_create(&philo[i].thread, NULL,
				&dinner, (void *)&philo[i]))
			return (free_msg("creating threads\n", philo), false);
	return (true);
}

bool	set_philo(t_philo *philo, t_data *data)
{
	if (data->n_philo == 1)
	{
		if (pthread_create(&philo[0].thread, NULL, &one, (void *)&philo[0]))
			return (free_msg("creating threads\n", philo), false);
	}
	else if (create_threads(philo, data) == false)
		return (false);
	return (data->create_threads = true, true);
}
