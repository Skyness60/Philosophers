/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:24:15 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 06:38:34 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	free_msg(char *msg, t_philo *philo)
{
	int	i;

	i = -1;
	if (philo)
		if (philo->data->create_threads == true)
			while (++i < philo->data->n_philo)
				if (pthread_join(philo[i].thread, NULL))
					return ;
	write(2, "Error: ", 8);
	write(2, msg, ft_strlen(msg));
}
