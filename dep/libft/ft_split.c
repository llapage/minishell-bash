/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:52:01 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 16:32:23 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_split_count_strings(char const *s, char c)
{
	size_t	nbr_strings;

	nbr_strings = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			nbr_strings++;
		while (*s && *s != c)
			s++;
	}
	return (nbr_strings);
}

static void	ft_split_free_mem(char **split_array, size_t string_nbr)
{
	if (string_nbr)
		while (string_nbr--)
			free(split_array[string_nbr]);
	free(split_array);
}

static int	ft_split_make_string(char const *s, \
		char c, char **split_array, size_t string_nbr)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	split_array[string_nbr] = malloc((len + 1) * sizeof(char));
	if (!(split_array[string_nbr]))
	{
		ft_split_free_mem(split_array, string_nbr);
		return (0);
	}
	split_array[string_nbr][len] = '\0';
	while (len-- > 0)
		split_array[string_nbr][len] = s[len];
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split_array;
	size_t	nbr_strings;
	size_t	string_nbr;

	if (!(s))
		return (0);
	nbr_strings = ft_split_count_strings(s, c);
	split_array = malloc((nbr_strings + 1) * sizeof(char *));
	if (!(split_array))
		return (0);
	split_array[nbr_strings] = 0;
	string_nbr = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			if (!(ft_split_make_string(s, c, split_array, string_nbr++)))
				return (0);
		while (*s && *s != c)
			s++;
	}
	return (split_array);
}
