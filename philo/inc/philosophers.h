/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 06:11:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/06 07:08:33 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/time.h>
# include "../garbage_collector/include/garbage_collector.h"

# define SLEEPW   "\033[1;33m is sleeping\033[0m"
# define FORKW    "\033[1;32m has taken a fork\033[0m"
# define EATW     "\033[1;32m is eating\033[0m"
# define THINKW   "\033[1;35m is thinking\033[0m"
# define DIEDW    "\033[1;31m died\033[0m"

typedef enum s_state
{
	SLEEP,
	FORK,
	EAT,
	THINK,
	DIED
}	t_state;

typedef enum s_actions
{
	LOCK,
	UNLOCK,
	DESTROY,
}	t_actions;

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	bool			bool_meals;
	int				death;
	long			start;
	int				finish_meal;
	bool			create_threads;
	t_garb_c		*trash;
	pthread_mutex_t	finish_meal_mtx;
	pthread_mutex_t	num_meals_mtx;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	write_mtx;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				num_meals;
	int				leave_dinner_table;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	pthread_mutex_t	*finish_meal_mtx;
	pthread_mutex_t	*num_meals_mtx;
	pthread_mutex_t	*last_meal_mtx;
	pthread_mutex_t	*death_mtx;
	pthread_mutex_t	*write_mtx;
}	t_philo;

bool			init_data(t_data *data, char **argv);
void			init_philos(t_philo *p, t_data *data, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(t_data *data, int len);
int				atoi_phil(char *str);
void			write_action(t_philo *philo, t_state action);
void			sleepy_time(int time);
int				get_time(void);
void			the_end(t_data data, pthread_mutex_t *forks);
void			take_forks(t_philo *philo);
int				get_death(t_data *data);
void			set_death(t_data *data, int death);
bool			check_bool(t_philo *philo);
void			protect_mutex(int action, pthread_mutex_t *mutex);
bool			create_threads(t_philo *philo, t_data *data);
bool			set_philo(t_philo *philo, t_data *data);
bool			init_simulation(t_philo *philo, t_data *data);
void			free_msg(char *msg, t_philo *philo);

#endif