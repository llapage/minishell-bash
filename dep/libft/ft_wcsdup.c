/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:46:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/04/07 20:43:16 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_wcsdup(const wchar_t *src)
{
	wchar_t	*dest;
	size_t	len;

	len = ft_wcslen(src);
	dest = malloc((len + 1) * sizeof(wchar_t));
	if (!(dest))
		return (0);
	dest[len] = '\0';
	while (len-- > 0)
		dest[len] = src[len];
	return (dest);
}
