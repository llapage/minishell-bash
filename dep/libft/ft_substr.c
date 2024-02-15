/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:25:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 16:24:47 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	substr_len;

	if (!(s))
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		substr_len = 0;
	else
		substr_len = s_len - start;
	if (substr_len > len)
		substr_len = len;
	substr = malloc((substr_len + 1) * sizeof(char));
	if (!(substr))
		return (0);
	substr[substr_len] = '\0';
	while (substr_len-- > 0)
		substr[substr_len] = s[start + substr_len];
	return (substr);
}
