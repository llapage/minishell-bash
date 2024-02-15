/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:49:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 16:25:50 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	len;

	if ((!(s1)) || (!(s2)))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc((len + 1) * sizeof(char));
	if (!(joined_str))
		return (0);
	while (*s1)
		*joined_str++ = *s1++;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	joined_str -= len;
	return (joined_str);
}
