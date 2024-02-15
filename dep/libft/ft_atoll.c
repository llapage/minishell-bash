/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:01:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/19 18:15:37 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	llong_len(long long n)
{
	if (n < 10)
		return (1);
	return (1 + llong_len(n / 10));
}

static long long	ft_atoll_2(const char *s, int pos, int sign, long long res)
{
	if (!(s[pos]))
		return (sign * res);
	if (!(ft_isdigit(s[pos])))
		return (0);
	if (res < LLONG_MAX / 10
		&& (s[pos] >= '0' && s[pos] <= '9')
		&& (!((s[pos + 1]))))
		return (sign * (res * 10 + s[pos] - '0'));
	if (res == LLONG_MAX / 10
		&& (s[pos] >= '0' && s[pos] <= '9')
		&& (!((s[pos + 1])))
		&& ((sign == -1 && s[pos] <= '8')
			|| s[pos] <= '7'))
		return (sign * (res * 10 + s[pos] - '0'));
	if (sign == 1)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

long long	ft_atoll(const char *s)
{
	long long	res;
	int			sign;
	int			len;
	int			pos;

	if ((!(s)))
		return (0);
	len = 0;
	res = 0;
	sign = 1;
	pos = 0;
	if (s[pos] == '+' || s[pos] == '-')
		if (s[pos++] == '-')
			sign = -1;
	while (s[pos] == '0')
		pos++;
	while (s[pos] >= '0' && s[pos] <= '9'
		&& len < llong_len(LLONG_MAX) - 1)
	{
		res = res * 10 + s[pos++] - '0';
		len++;
	}
	return (ft_atoll_2(s, pos, sign, res));
}
