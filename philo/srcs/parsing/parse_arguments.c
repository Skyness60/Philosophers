/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:12:33 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 13:12:57 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_arguments(int ac, char **av, t_global *global)
{
	if (ac < 5 || ac > 6)
		return (printf("\033[33mUsage: \033[34m%s \033[31m%s\033[0m", \
		av[0], ERR_NUM_ARGS), true);
	if (input_checker(av))
		return (true);
	if (init(&global, av, ac) == true)
		return (true);
	if (global->num_philo == 1)
		return (philo_one(&global));
	if (thread_init(&global))
		return (true);
	ft_exit(&global);
	return (false);
}
