/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:26:13 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:34:18 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(void)
{
	if ((g_forks = sem_open("forks", O_CREAT, S_IRWXU, g_params[0]))
	== SEM_FAILED)
		return (error_return(SEM_FAIL));
	if ((g_alive = sem_open("alive", O_CREAT, S_IRWXU, 1))
	== SEM_FAILED)
		return (error_return(SEM_FAIL));
	if ((g_full = sem_open("full", O_CREAT, S_IRWXU, g_params[0]))
	== SEM_FAILED)
		return (error_return(SEM_FAIL));
	return (0);
}

static void	*monitoring(void *arg)
{
	int			i;
	t_th_info	*info;

	info = arg;
	while (1)
	{
		if ((cur_time() - info->interval_start) / 1000 > g_params[1])
		{
			put_stamp(info->thread_id, " died\n");
			sem_wait(g_alive);
			break ;
		}
		i++;
	}
	return (NULL);
}

static int	create_threads(int i)
{
	pthread_t	thread;
	pthread_t	monitor;
	t_th_info	thread_info;

	thread_info.thread_id = i;
	thread_info.cycle = 0;
	thread_info.interval_start = cur_time();
	if (pthread_create(&thread, NULL, routine, &thread_info) ||
	pthread_detach(thread))
		return (error_return(THREAD_FAIL));
	if (pthread_create(&monitor, NULL, monitoring, &thread_info) ||
	pthread_join(monitor, NULL))
		return (error_return(THREAD_FAIL));
	return (0);
}

static int	threading(void)
{
	int		i;
	int		ret;
	int		status;
	int		pid;
	int		pids[g_params[0]];

	g_time = cur_time();
	i = 0;
	while (i < g_params[0])
	{
		pid = fork();
		if (pid == 0)
			if ((ret = create_threads(i)))
				return (ret);
		pids[i] = pid;
		if (g_alive->__size[0] == 0)
			exit(0);
		i++;
	}
	waitpid(-1, &status, 0);
	while (i-- > 0 && pids[i])
		kill(pids[i], SIGKILL);
	return (0);
}

int			main(int argc, char **argv)
{
	sem_unlink("forks");
	sem_unlink("alive");
	sem_unlink("full");
	if (fill_dinner_params(argc, argv))
		return (EXIT_FAILURE);
	if (init_mutexes())
		return (EXIT_FAILURE);
	if (threading())
		return (EXIT_FAILURE);
}
