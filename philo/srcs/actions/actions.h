/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:21 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 14:13:31 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include <sys/time.h>
# include "../../includes/philo.h"

typedef unsigned int		t_useconds;

uint64_t	get_time(void);
void		*routine(void *philo_pointer);
bool		philo_one(t_global *global);
int			ft_usleep(t_useconds time);

#endif // !ACTIONS_H