/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:03:25 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 13:12:48 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../includes/philo.h"

void	ft_exit(t_global *global);
void	clear_data(t_global *global);
bool	input_checker(char **av);
bool	parse_arguments(int ac, char **av, t_global *global);
bool	init(t_global *global, char **av, int ac);

#endif