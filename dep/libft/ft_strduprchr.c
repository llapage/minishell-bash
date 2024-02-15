/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduprchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:52:18 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/12 07:19:33 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strduprchr(const char *src, char c)
{
	char	*part_str;
	size_t	len;
	size_t	c_pos;

	len = 0;
	while (src[len])
		len++;
	c_pos = len;
	while (c_pos && src[c_pos] != c)
		c_pos--;
	if (c_pos || src[c_pos] == c)
		len = c_pos;
	part_str = malloc((len + 1) * sizeof(char));
	if (!(part_str))
		return (NULL);
	part_str[len] = '\0';
	while (len-- != 0)
		part_str[len] = src[len];
	return (part_str);
}
