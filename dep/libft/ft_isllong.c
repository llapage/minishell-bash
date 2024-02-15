/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isllong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:01:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/19 18:16:52 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(int neg, long long res, char *s)
{
	if (!(ft_isdigit(*s)))
		return (0);
	if (res < 922337203685477580
		&& (!(*(s + 1))))
		return (1);
	if (res == 922337203685477580
		&& (!(*(s + 1)))
		&& ((neg && *s <= '8')
			|| *s <= '7'))
		return (1);
	return (0);
}

int	ft_isllong(char *s)
{
	long long	res;
	int			neg;
	int			len;
	int			zero;

	if (!(s))
		return (0);
	len = 0;
	res = 0;
	neg = 0;
	zero = 0;
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			neg = 1;
	while (*s == '0' && s++)
		zero = 1;
	while (*s >= '0' && *s <= '9' && len < 18)
	{
		res = res * 10 + *s++ - '0';
		len++;
	}
	if ((!(*s)) && (len || zero))
		return (1);
	return (check_overflow(neg, res, s));
}
