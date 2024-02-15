/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strstr_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 18:17:40 by llapage           #+#    #+#             */
/*   Updated: 2023/09/19 18:16:27 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define CASE_SENSITIVE 1

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_strstr_tab(char ***tab, int size, int mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if ((mode == CASE_SENSITIVE
					&& ft_strcmp((*tab)[i], (*tab)[j]) > 0)
				|| (mode != CASE_SENSITIVE
					&& ft_strcasecmp((*tab)[i], (*tab)[j]) > 0))
				ft_swap(&(*tab)[i], &(*tab)[j]);
			j++;
		}
		i++;
	}
}
