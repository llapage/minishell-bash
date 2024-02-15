/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:08:51 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/10 00:48:12 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumeric(char *str)
{
	if (!(str))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
		if (!(ft_isdigit(*(str++))))
			return (0);
	return (1);
}
