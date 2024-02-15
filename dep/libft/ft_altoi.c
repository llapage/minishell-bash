/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_altoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 09:14:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/31 05:10:11 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	altoi_skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
}

static int	verify_result(char current_character, int len \
		, long long res, int sign)
{
	if ((current_character && (!(ft_isspace(current_character)))) \
			|| len == 0 \
			|| len > 10 \
			|| res * sign < INT_MIN \
			|| res * sign > INT_MAX)
		return (0);
	return (1);
}

int	ft_altoi(char **str, int *nbr)
{
	long long	res;
	int			sign;
	int			len;

	altoi_skip_spaces(str);
	sign = 1;
	if (**str == 43 || **str == 45)
	{
		if (**str == 45)
			sign = -1;
		(*str)++;
	}
	len = 0;
	res = 0;
	while (**str && **str >= '0' && **str <= '9')
	{
		res = res * (long long)10 + *(*str)++ - '0';
		len++;
	}
	if (!(verify_result(**str, len, res, sign)))
		return (0);
	*nbr = (int)res * sign;
	altoi_skip_spaces(str);
	return (1);
}
