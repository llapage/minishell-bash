/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 01:25:42 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:23:02 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	while (*s1)
		if (ft_tolower(*s1++) != ft_tolower(*s2++))
			return (ft_tolower(*--s1) - ft_tolower(*--s2));
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
