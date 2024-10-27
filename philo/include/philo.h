/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:16:22 by sperron           #+#    #+#             */
/*   Updated: 2024/10/27 13:27:39 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "../garbage_collector/include/garbage_collector.h"

typedef struct s_garbage_c	t_garbage_c;

typedef struct s_data		t_data;

typedef enum e_mutex_action
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}	t_mutex_action;

typedef enum e_thread_action
{
	CREATE,
	JOIN,
	DETACH
}	t_thread_action;

typedef enum e_philo_state
{
	EATING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	SLEEPING,
	THINKING,
	DEAD
}	t_philo_state;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	long			eaten_nb;
	bool			full;
	bool			dead;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	long			start_time;
	long			ready_nb;
	bool			finish;
	t_garbage_c		*trash;
	pthread_t		monitor;
	pthread_mutex_t	dinner_mtx;
	pthread_mutex_t	write_mtx;
	t_fork			*forks;
	t_philo			*philos;
}	t_data;

int			parsing(t_data *data, char **av);
int			handle_mutex(pthread_mutex_t *mutex, t_mutex_action action);
int			init(t_data *data);
void		destroy_all(t_data *data);
long		get_time(bool second, bool ms);
int			handle_thread(pthread_t *thread, void *(*f)(void *), void *arg, \
t_thread_action action);
void		set_bool(bool *to_set, bool value, pthread_mutex_t *mutex);
void		set_long(long *to_set, long value, pthread_mutex_t *mutex);
bool		get_bool(bool *to_get, pthread_mutex_t *mutex);
long		get_long(long *to_get, pthread_mutex_t *mutex);
void		increment_long_with_mutex(long *dest, pthread_mutex_t *mtx);
void		print_action(t_philo_state state, t_philo *philo);
void		*monitor(void *data);
void		start_dining(t_data *data);
bool		end_dinning(t_data *data);
void		precise_usleep(long time);
#endif // !PHILO_H