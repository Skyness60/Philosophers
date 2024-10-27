/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:24:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 13:25:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	not_too_long(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i > 10)
		return (0);
	return (1);
}

static long	ft_atol(char *s)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((s[i] == ' ') || (s[i] > 8 && s[i] < 14))
		i++;
	if ((s[i] < '0' || s[i] > '9') && s[i] != '+')
		return (-1);
	if (s[i] == '+')
		i++;
	if (not_too_long(s + i) == 0)
		return (-1);
	while (s[i])
	{
		if (s[i] < '0' && s[i] > '9')
			return (-1);
		res = res * 10 + (s[i++] - '0');
	}
	if (res > INT_MAX)
		return (-1);
	return (res);
}

int	parsing(t_data *data, char **av)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	data->nb_meals = -1;
	while (av[++i])
	{
		result = ft_atol(av[i]);
		if (result == -1)
			return (-1);
		if (i == 1)
			data->nb_philo = (int)result;
		else if (i == 2)
			data->time_to_die = result;
		else if (i == 3)
			data->time_to_eat = result;
		else if (i == 4)
			data->time_to_sleep = result;
		else if (i == 5)
			data->nb_meals = result;
	}
	return (0);
}
