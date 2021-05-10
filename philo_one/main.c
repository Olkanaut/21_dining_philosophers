/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:26:13 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 22:03:43 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(void)
{
	int		i;

	i = 0;
	if (!(g_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *
	g_params[0])))
		return (error_return(MALLOC_FAIL));
	while (i < g_params[0])
	{
		if (pthread_mutex_init(&g_forks[i], NULL))
			return (error_return(MUTEX_FAIL));
		i++;
	}
	if (pthread_mutex_init(&g_mutex, NULL))
		return (error_return(MUTEX_FAIL));
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
	int			i;

	while (1)
	{
		i = 0;
		while (i < g_params[0])
		{
			if ((cur_time() - g_thread_info[i].interval_start) / 1000
			> g_params[1])
			{
				put_stamp(g_thread_info[i].thread_id, " died\n");
				clear_exit(0);
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
	if (pthread_create(&monitor, NULL, monitoring, &g_thread_info))
		return (error_return(THREAD_FAIL));
	join_threads(threads);
	return (0);
}

int			main(int argc, char **argv)
{
	if (fill_dinner_params(argc, argv))
		return (EXIT_FAILURE);
	if (init_mutexes())
		return (EXIT_FAILURE);
	if (threading())
		return (EXIT_FAILURE);
}
