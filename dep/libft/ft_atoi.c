/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:16:06 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 14:28:17 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	atoi_check_overflow(int len, int sign, unsigned long long result)
{
	if (len > 19 || result > LLONG_MAX)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;
	int					len;

	len = 0;
	result = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	sign = 1;
	if (*str == 43 || *str == 45)
		if (*str++ == 45)
			sign = -1;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str++ - '0';
		len++;
	}
	return (atoi_check_overflow(len, sign, result));
}
