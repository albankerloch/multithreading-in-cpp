/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <akerloc-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:40:22 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/10 17:52:08 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static long long	ft_puiss_dix(int n)
{
	long long result;

	if (n == 0)
	{
		result = 1;
	}
	else
	{
		result = 10 * ft_puiss_dix(n - 1);
	}
	return (result);
}

static void			ft_rec(long long a, int p, char str[50], int t)
{
	char		c;
	long long	i;
	long long	b;

	i = ft_puiss_dix(p);
	c = a / i + 48;
	str[t] = c;
	if (p != 0)
	{
		b = a % i;
		ft_rec(b, p - 1, str, t + 1);
	}
}

void				ft_putlnbr_str(long long a, char str[50])
{
	int			p;
	long long	b;

	b = a;
	p = 0;
	while ((b % 10) != b)
	{
		b = b / 10;
		p++;
	}
	ft_rec(a, p, str, 0);
	str[p + 1] = '\0';
}