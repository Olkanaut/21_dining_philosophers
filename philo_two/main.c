/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:26:13 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:50:29 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(void)
{
	if ((g_forks = sem_open("forks", O_CREAT, S_IRWXU, g_params[0])) ==
	SEM_FAILED)
		return (error_return(SEM_FAIL));
	if ((g_alive = sem_open("alive", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (error_return(SEM_FAIL));
	return (0);
}

static void	join_threads(pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < g_params[0])
	{
		if (pthread_join(threads[i], NULL))
			return ;
		i++;
	}
}

static void	*monitoring(void *arg)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < g_params[0])
		{
			if ((cur_time() - g_thread_info[i].interval_start) / 1000 >
			g_params[1])
			{
				put_stamp(g_thread_info[i].thread_id, " died\n");
				exit(0);
			}
			i++;
		}
	}
	return (NULL);
}

static int	threading(void)
{
	pthread_t	threads[g_params[0]];
	pthread_t	monitor;
	t_th_info	thread_info[g_params[0]];
	int			i;

	g_thread_info = thread_info;
	g_time = cur_time();
	i = 0;
	while (i < g_params[0])
	{
		g_thread_info[i].thread_id = i;
		g_thread_info[i].cycle = 0;
		g_thread_info[i].interval_start = cur_time();
		if (pthread_create(&threads[i], NULL, routine, &g_thread_info[i]))
			return (error_return(THREAD_FAIL));
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, NULL) ||
	pthread_detach(monitor))
		return (error_return(THREAD_FAIL));
	join_threads(threads);
	return (0);
}

int			main(int argc, char **argv)
{
	sem_unlink("forks");
	sem_unlink("alive");
	if (fill_dinner_params(argc, argv))
		return (EXIT_FAILURE);
	if (init_mutexes())
		return (EXIT_FAILURE);
	if (threading())
		return (EXIT_FAILURE);
}
