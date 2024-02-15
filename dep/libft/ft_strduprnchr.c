/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduprnchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:52:18 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/05 15:55:04 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strduprnchr(const char *src, char c, size_t n)
{
	char	*part_str;
	size_t	len;
	size_t	c_pos;

	len = 0;
	while (src[len])
		len++;
	c_pos = len;
	while (n)
	{
		if (src[c_pos] == c)
			n--;
		if ((!(n)) || (!(c_pos)))
			break ;
		c_pos--;
	}
	if (!(n))
		len = c_pos;
	part_str = malloc((len + 1) * sizeof(char));
	part_str[len] = '\0';
	while (len-- != 0)
		part_str[len] = src[len];
	return (part_str);
}
