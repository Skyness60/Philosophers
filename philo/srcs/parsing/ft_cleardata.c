/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleardata.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:54:53 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 15:05:11 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_data(t_global *global)
{
	if (global->tid)
		free(global->tid);
	if (global->philo)
		free(global->philo);
	if (global->forks)
		free(global->forks);
}
