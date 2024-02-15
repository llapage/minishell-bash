/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:34:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/19 18:16:59 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char const *s2)
{
	char	*joined_str;
	size_t	len;
	size_t	i;

	if ((!(s1)) || (!(s2)))
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = malloc((len + 1) * sizeof(char));
	if (!(joined_str))
	{
		free(s1);
		s1 = NULL;
		return (0);
	}
	i = 0;
	while (s1[i])
		*joined_str++ = s1[i++];
	free(s1);
	s1 = NULL;
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	joined_str -= len;
	return (joined_str);
}
