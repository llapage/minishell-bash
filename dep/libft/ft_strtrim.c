/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:59:13 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/21 14:55:06 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strtrim_len(char const *s1, char const *set, size_t s1_len)
{
	size_t	trim_count;
	size_t	i;

	trim_count = 0;
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i++]))
		trim_count++;
	i = s1_len;
	while (i-- > 0 && ft_strchr(set, s1[i]) && trim_count < s1_len)
		trim_count++;
	return (s1_len - trim_count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	size_t	s1_len;
	size_t	trimmed_str_len;

	if (!(s1))
		return (0);
	if (!(set))
		return ((char *)s1);
	s1_len = ft_strlen(s1);
	trimmed_str_len = ft_strtrim_len(s1, set, s1_len);
	trimmed_str = malloc((trimmed_str_len + 1) * sizeof(char));
	if (!(trimmed_str))
		return (0);
	trimmed_str[trimmed_str_len] = '\0';
	if (trimmed_str_len > 0)
	{
		s1 += s1_len - 1;
		while (ft_strchr(set, *s1))
			s1--;
		while (trimmed_str_len-- > 0)
			trimmed_str[trimmed_str_len] = *s1--;
	}
	return (trimmed_str);
}
