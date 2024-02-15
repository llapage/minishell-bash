/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:25:44 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:24:06 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strstrlen(const char **src)
{
	size_t	len;

	len = 0;
	if (!(src))
		return (0);
	while (src[len])
		len++;
	return (len);
}
