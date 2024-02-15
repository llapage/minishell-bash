/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stowcedup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:46:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/13 11:06:10 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_stowcedup(const char *src, int *error)
{
	wchar_t	*dest;
	size_t	len;

	if (!(src))
		return (0);
	len = ft_strlen(src);
	dest = malloc((len + 1) * sizeof(wchar_t));
	if (!(dest))
	{
		*error = 1;
		return (0);
	}
	dest[len] = '\0';
	while (len-- > 0)
		dest[len] = src[len];
	return (dest);
}
