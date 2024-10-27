/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:29:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 12:13:37 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data		data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, av) == -1 && data.nb_philo == 0)
			return (printf("Please enter a correct args, please"), 1);
		data.trash = malloc(sizeof(t_garb_c));
		data.trash->ptr_arr = NULL;
		if (init(&data) == -1)
			return (destroy_all(&data), free_all(data.trash), 1);
		start_dining(&data);
		destroy_all(&data);
		free_all(data.trash);
	}
	else
		return (printf("Error: wrong number of arguments\n"), 1);
}
