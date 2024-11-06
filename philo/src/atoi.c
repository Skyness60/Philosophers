/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 04:24:28 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 05:35:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static int	is_clean(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (is_digit(str[i]) == false)
			return (-1);
	return (0);
}

int	atoi_phil(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = -1;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9')
			res = (res * 10) + (str[i] - '0');
	if (is_clean(str) == -1)
		return (-1);
	if (res > 2147483647)
		return (-1);
	return ((int)res);
}
