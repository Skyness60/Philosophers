/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:34:16 by sperron           #+#    #+#             */
/*   Updated: 2024/09/21 14:11:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include "../srcs/utils/mutex/mutex_utils.h"
# include "../srcs/utils/notlibft/notlibft.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/actions/actions.h"

# define ERR_NUM_ARGS " :\n- number_of_philosophers\n- time_to_die\n- \
time_to_eat\n- time_to_sleep\n- [number_of_times_each_philosopher_must_eat] \n"
# define ERR_INPUT_CHAR "\033[31mINVALID INPUT CHARACTER\033[0m"
# define ERR_INPUT_VALUE "\033[31mINVALID INPUT VALUES\033[0m"

struct	s_global;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}				t_state;

typedef enum e_statefork
{
	OPEN = false,
	CLOSE = true
}				t_statefork;

typedef struct s_philo
{
	struct s_global	*global;
	int				id;
	t_state			state;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_mutex			lock;
	pthread_t		thread;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		timer;
	int				eat_count;
	int				times_eaten;
	struct timeval	last_meat;
	t_mutex			state_mutex;
	t_mutex			last_meal_mutex;
}				t_philo;

typedef struct s_fork
{
	t_mutex		mutex;
	t_statefork	state;
}				t_fork;

typedef struct s_global
{
	pthread_t	*tid;
	t_philo		*philo;
	t_fork		*forks;
	t_mutex		log_mutex;
	t_mutex		lock;
	t_mutex		write;
	int			num_philo;
	int			eat_count;
	int			finish;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	timer;
	int			i_eat;
	int			meals_nb;
	int			i_died;
}				t_global;

bool	parse_arguments(int ac, char **av, t_global *global);

#endif