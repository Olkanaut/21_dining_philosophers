/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:32:37 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:38:10 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		fill_dinner_params(int argc, char **argv)
{
	int		i;

	if (argc < 5 || argc > 6)
	{
		write(1, "You have entered wrong number of arguments. Exit.\n", 50);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		g_params[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (argc == 5)
		g_params[4] = -1;
	return (0);
}

int		error_return(char *text)
{
	write(1, text, ft_strlen(text));
	return (1);
}

void	clear_exit(int status)
{
	sem_close(g_forks);
	sem_close(g_alive);
	sem_close(g_full);
	sem_unlink("forks");
	sem_unlink("alive");
	sem_unlink("full");
	exit(status);
}

long	cur_time(void)
{
	struct timeval	start;
	long			ms;

	gettimeofday(&start, NULL);
	ms = start.tv_sec * 1000000;
	ms += start.tv_usec;
	return (ms);
}

int		ft_atoi(const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
	{
		if (res > (res * 10 + (*str - '0')))
			return (sign > 0 ? -1 : 0);
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
