/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:00:21 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 13:10:34 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "notlibft.h"

long	ft_atoi(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		result *= 10 + (*str - '0');
		str++;
	}
	result *= sign;
	if (result > INT_MAX || result < INT_MIN)
		return (LONG_MAX);
	return ((long)result);
}
