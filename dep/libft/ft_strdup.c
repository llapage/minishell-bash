/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:06:59 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 14:33:06 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*string_duplicate;
	size_t	len;

	len = ft_strlen(s1);
	string_duplicate = malloc((len + 1) * sizeof(char));
	if (!(string_duplicate))
		return (0);
	string_duplicate[len] = '\0';
	while (len-- != 0)
		string_duplicate[len] = s1[len];
	return (string_duplicate);
}
