/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:13:59 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 13:49:10 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

bool	philo_one(t_global *global)
{
	global->timer = get_time();
	if (pthread_create(&global->tid[0], NULL, &routine, &global->philo[0]))
		return (printf("\033[31mTHREADS ERROR\n\033[0m"), ft_exit(NULL), true);
	pthread_detach(global->tid[0]);
	while (global->i_died == 0)
		ft_usleep(0);
	return (ft_exit(global), false);
}
