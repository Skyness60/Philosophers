/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:12:33 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 15:10:18 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_arguments(int ac, char **av, t_global *global)
{
	if (ac < 5 || ac > 6)
		return (printf("\033[33mUsage: \033[34m%s \033[31m%s\033[0m", \
		av[0], ERR_NUM_ARGS), true);
	if (input_check(av))
		return (true);
	if (init(&global, av, ac))
	return (false);
}
