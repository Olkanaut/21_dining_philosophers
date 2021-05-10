/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:56:17 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:39:00 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <ctype.h>

# define SEM_FAIL		"sem_open() failed\n"
# define THREAD_FAIL	"pthread function failed\n"
# define MALLOC_FAIL	"malloc() failed\n"

/*
** dinner params
** 0 - philos number
** 1 - time_live
** 2 - time_eat
** 3 - time_sleep
** 4 - cycles
*/

typedef struct	s_th_info
{
	long		thread_id;
	long		cycle;
	long		interval_start;
}				t_th_info;

long			g_params[5];
sem_t			*g_forks;
sem_t			*g_alive;
sem_t			*g_full;
long			g_time;

int				main(int argc, char **argv);
void			*routine(void *arg);
size_t			ft_strlen(const char *str);
void			put_stamp(long id, char *status);
int				fill_dinner_params(int argc, char **argv);
int				error_return(char *text);
void			clear_exit(int status);
long			cur_time(void);
int				ft_atoi(const char *str);

#endif
