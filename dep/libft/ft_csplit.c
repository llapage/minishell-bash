/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:33:37 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/31 13:59:55 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_csplit(char const *s, size_t *arr)
{
	char	**s_arr;
	size_t	size;
	size_t	el;
	size_t	len;

	if (!(s))
		return (NULL);
	size = arr[0];
	s_arr = malloc((size + 1) * sizeof(char *));
	if (!(s_arr))
		return (NULL);
	s_arr[size] = NULL;
	el = 0;
	while (el < size)
	{
		len = arr[el + 1];
		s_arr[el] = malloc((len + 1) * sizeof(char));
		s_arr[el][len] = '\0';
		ft_memcpy(s_arr[el], s, len);
		s += len;
		el++;
	}
	return (s_arr);
}
