/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strracat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:51:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/17 11:57:25 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strracat(char **dest, char *src)
{
	char	*temp;
	size_t	temp_len;
	size_t	src_len;

	temp = ft_pstrdup(*dest);
	free(*dest);
	*dest = 0;
	if (!(temp))
		return (0);
	temp_len = ft_strlen(temp);
	src_len = ft_strlen(src);
	*dest = malloc((temp_len + src_len + 1) * sizeof(char));
	if (!(*dest))
	{
		free(temp);
		return (0);
	}
	(*dest)[temp_len + src_len] = '\0';
	ft_strcncpy(*dest, temp, temp_len);
	free(temp);
	*dest += temp_len;
	ft_strcncpy(*dest, src, src_len);
	*dest -= temp_len;
	return (1);
}
