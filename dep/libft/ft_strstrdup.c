/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:27:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:23:50 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strstrdup(const char **src)
{
	char	**new_strstr;
	size_t	len;
	size_t	i;

	len = ft_strstrlen(src);
	new_strstr = malloc((len + 1) * sizeof(char *));
	new_strstr[len] = 0x00;
	i = 0;
	while (i < len)
	{
		new_strstr[i] = ft_strdup(src[i]);
		i++;
		if (!(new_strstr))
		{
			while (i-- != 0)
				free(new_strstr[i]);
			free(new_strstr);
			return (NULL);
		}
	}
	return (new_strstr);
}
