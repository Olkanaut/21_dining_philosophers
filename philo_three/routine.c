/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:17:05 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:36:08 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (info->cycle == g_params[4])
		sem_wait(g_full);
	if (g_full->__size[0] == 0)
		clear_exit(0);
	sem_post(g_forks);
	sem_post(g_forks);
}

void		*routine(void *arg)
{
	t_th_info	*info;

	info = arg;
	while (1)
	{
		put_stamp(info->thread_id, " is thinking\n");
		eating_time(info);
		put_stamp(info->thread_id, " is sleeping\n");
		usleep(g_params[3] * 1000);
	}
}
