/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:39:07 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/05 02:13:43 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupchr(const char *src, char c)
{
	char	*part_str;
	size_t	len;

	len = 0;
	while (src[len] && src[len] != c)
		len++;
	part_str = malloc((len + 1) * sizeof(char));
	if (!(part_str))
		return (NULL);
	part_str[len] = '\0';
	while (len-- != 0)
		part_str[len] = src[len];
	return (part_str);
}
