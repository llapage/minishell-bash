/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:36:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 14:33:56 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size > src_len)
		dst[src_len] = '\0';
	else if (size != 0)
		dst[size - 1] = '\0';
	while (size-- > 1 && *src)
		*dst++ = *src++;
	return (src_len);
}
