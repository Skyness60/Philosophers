/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:27:19 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 15:10:59 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	input_checker(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isspace(av[i][j]))
			{
				j++;
				continue ;
			}
			if ((av[i][j] < 48 || av[i][j] > 57))
				return (printf("%s\n", ERR_INPUT_CHAR), ft_error(NULL), \
				true);
			j++;
		}
		i++;
	}
	return (true);
}
