/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:18:29 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 13:54:52 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include <sys/types.h>

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("\033[31mget_time Error\n\033[0m"), ft_error(NULL));
	return ((tv.tv_usec / 1000) + (tv.tv_sec * (uint64_t)1000));
}

int	ft_usleep(t_useconds time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time - start) < time)
		usleep(time / 10);
	return (false);
}
