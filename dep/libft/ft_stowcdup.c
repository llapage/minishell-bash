/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stowcdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:46:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/04/12 10:45:05 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_stowcdup(const char *src)
{
	wchar_t	*dest;
	size_t	len;

	if (!(src))
		return (0);
	len = ft_strlen(src);
	dest = malloc((len + 1) * sizeof(wchar_t));
	if (!(dest))
		return (0);
	dest[len] = '\0';
	while (len-- > 0)
		dest[len] = src[len];
	return (dest);
}
