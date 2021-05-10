/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_stamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bshang <bshang@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:14:53 by bshang            #+#    #+#             */
/*   Updated: 2021/01/06 18:37:03 by bshang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t			ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int i1;
	unsigned int i2;
	unsigned int res;

	if ((dest || src) && size != 0)
	{
		i1 = 0;
		i2 = 0;
		res = 0;
		while (dest[i2] && i2 < size)
			i2++;
		res = ft_strlen(src) + i2;
		if (size == i2)
			return (res);
		while (src[i1] && i2 + i1 < size - 1)
		{
			dest[i2 + i1] = src[i1];
			i1++;
		}
		dest[i2 + i1] = '\0';
		return (res);
	}
	return (ft_strlen(src));
}

static int		ft_num_len(int nbr)
{
	int		len;

	len = 0;
	while (nbr <= -10 || nbr >= 10)
	{
		nbr /= 10;
		len++;
	}
	if (nbr < 0)
		len++;
	return (len);
}

static char		*ft_itoa_mod(int nbr)
{
	int		len;
	char	*str;

	len = 0;
	len = ft_num_len(nbr);
	if (!(str = (char*)malloc(sizeof(*str) * (len + 2))))
		return (NULL);
	str[len + 1] = '\0';
	while (len >= 0)
	{
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

void			put_stamp(long id, char *status)
{
	char	buf[50];
	long	time;
	char	*tmp;

	time = (cur_time() - g_time) / 1000;
	tmp = ft_itoa_mod(time);
	buf[0] = '\0';
	ft_strlcat(buf, tmp, 50);
	ft_strlcat(buf, "\t", 50);
	free(tmp);
	tmp = ft_itoa_mod(id);
	ft_strlcat(buf, tmp, 50);
	free(tmp);
	ft_strlcat(buf, status, 50);
	write(1, buf, ft_strlen(buf));
}
