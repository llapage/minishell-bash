/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:38:40 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 14:31:18 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	int		direction;

	if ((!(dst)) && (!(src)))
		return (dst);
	i = 0;
	direction = 1;
	if (src < dst)
	{
		i = n - 1;
		direction = -1;
	}
	while (n-- > 0)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i += direction;
	}
	return (dst);
}
