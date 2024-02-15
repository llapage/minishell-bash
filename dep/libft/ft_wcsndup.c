/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 09:46:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/04/07 20:55:01 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_wcsndup(const wchar_t *src, size_t n)
{
	wchar_t	*dest;
	size_t	len;

	len = ft_wcslen(src);
	if (len < n)
		n = len;
	dest = malloc((n + 1) * sizeof(wchar_t));
	if (!(dest))
		return (0);
	dest[n] = '\0';
	while (n-- > 0)
		dest[n] = src[n];
	return (dest);
}
