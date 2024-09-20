/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:54:38 by sperron           #+#    #+#             */
/*   Updated: 2024/09/20 12:02:00 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_UTILS_H
# define MUTEX_UTILS_H

# include <pthread.h>

typedef pthread_mutex_t		t_mutex;
typedef pthread_mutexattr_t	t_mutexattr;

void	mutex_init(t_mutex *mutex, const t_mutexattr *mutexattr);
void	mutex_lock(t_mutex *mutex);
void	mutex_unlock(t_mutex *mutex);
void	mutex_destroy(t_mutex *mutex);
#endif