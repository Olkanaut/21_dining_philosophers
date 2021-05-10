/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:17:05 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 16:38:57 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	everyone_is_full(void)
{
	int		i;
	int		cycle_check;

	i = 0;
	cycle_check = 0;
	if (g_params[4] == -1)
		return (0);
	pthread_mutex_lock(&g_mutex);
	while (i < g_params[0])
	{
		if (g_thread_info[i].cycle >= g_params[4])
			cycle_check++;
		i++;
	}
	pthread_mutex_unlock(&g_mutex);
	if (cycle_check >= g_params[0])
		return (1);
	return (0);
}

static int	choose_forks(int id, int mode)
{
	if (id < (id + 1) % g_params[0])
		return (mode ? (id + 1) % g_params[0] : id);
	return (mode ? id : (id + 1) % g_params[0]);
}

static void	eating_time(t_th_info *info)
{
	pthread_mutex_lock(&g_forks[choose_forks(info->thread_id, 0)]);
	put_stamp(info->thread_id, " has taken a fork\n");
	pthread_mutex_lock(&g_forks[choose_forks(info->thread_id, 1)]);
	put_stamp(info->thread_id, " has taken a fork\n");
	info->interval_start = cur_time();
	put_stamp(info->thread_id, " is eating\n");
	usleep(g_params[2] * 1000);
	info->cycle++;
	pthread_mutex_unlock(&g_forks[(info->thread_id + 1) % g_params[0]]);
	pthread_mutex_unlock(&g_forks[info->thread_id]);
}

void		*routine(void *arg)
{
	t_th_info	*info;

	info = arg;
	info->interval_start = cur_time();
	while (1)
	{
		put_stamp(info->thread_id, " is thinking\n");
		eating_time(info);
		if (everyone_is_full())
			clear_exit(0);
		put_stamp(info->thread_id, " is sleeping\n");
		usleep(g_params[3] * 1000);
	}
}

int			error_return(char *text)
{
	write(1, text, ft_strlen(text));
	return (1);
}
