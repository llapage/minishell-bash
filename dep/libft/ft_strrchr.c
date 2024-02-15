/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:59:10 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 12:07:59 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s_ptr;

	c = (char)c;
	s_ptr = s;
	s += ft_strlen(s);
	while (s >= s_ptr)
		if (*s-- == c)
			return ((char *)++s);
	return (0);
}
