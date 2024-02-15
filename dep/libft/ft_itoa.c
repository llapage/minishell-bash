/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:26:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 16:33:08 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_nbr_len(long long n)
{
	if (n < 0)
		return (1 + ft_itoa_nbr_len(-n));
	if (n < 10)
		return (1);
	return (1 + ft_itoa_nbr_len(n / 10));
}

static char	*ft_itoa_write(char *str, size_t len, long long n)
{
	size_t	start_index;

	start_index = 0;
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		start_index = 1;
		n *= -1;
	}
	while (len-- > start_index)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	len = ft_itoa_nbr_len((long long)n);
	str = malloc((len + 1) * sizeof(char));
	if (!(str))
		return (0);
	return (ft_itoa_write(str, len, (long long)n));
}
