/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:48:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/17 11:55:13 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcchr(char *str, char c, size_t n)
{
	size_t	len;

	if (!(str))
		return (0);
	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	if (len < n)
		n = len;
	str -= n;
	while (*str)
		if (*str++ == c)
			return (--str);
	return (0);
}
