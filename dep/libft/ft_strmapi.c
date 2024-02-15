/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:00:54 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 16:34:10 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapped_str;
	size_t	len;

	if ((!(s)) || (!(f)))
		return (0);
	len = ft_strlen(s);
	mapped_str = malloc((len + 1) * sizeof(char));
	if (!(mapped_str))
		return (0);
	mapped_str[len] = '\0';
	while (len-- > 0)
		mapped_str[len] = f(len, s[len]);
	return (mapped_str);
}
