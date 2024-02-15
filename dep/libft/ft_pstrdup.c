/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:50:13 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/20 13:48:02 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pstrdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = 0;
	if (s)
		len = ft_strlen(s);
	dup = malloc((len + 1) * sizeof(char));
	if (!(dup))
		return (0);
	dup[len] = '\0';
	while (len-- > 0)
		dup[len] = s[len];
	return (dup);
}
