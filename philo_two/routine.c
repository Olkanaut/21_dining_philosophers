/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:17:05 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 17:07:11 by bshang           ###   ########.fr       */
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
	while (i < g_params[0])
	{
		if (g_thread_info[i].cycle >= g_params[4])
			cycle_check++;
		i++;
	}
	if (cycle_check >= g_params[0])
		return (1);
	return (0);
}

static void	eating_time(t_th_info *info)
{
	sem_wait(g_forks);
	put_stamp(info->thread_id, " has taken a fork\n");
	sem_wait(g_forks);
	put_stamp(info->thread_id, " has taken a fork\n");
	info->interval_start = cur_time();
	put_stamp(info->thread_id, " is eating\n");
	usleep(g_params[2] * 1000);
	info->cycle++;
	sem_post(g_forks);
	sem_post(g_forks);
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
			exit(0);
		put_stamp(info->thread_id, " is sleeping\n");
		usleep(g_params[3] * 1000);
	}
}
