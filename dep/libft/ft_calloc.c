/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:00:34 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/12 12:50:00 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*return_ptr;
	size_t		allocation_size;

	if (size && count > ((size_t)-1) / size)
		return (0);
	allocation_size = count * size;
	return_ptr = malloc(allocation_size);
	if (!(return_ptr))
		return (0);
	while (allocation_size-- > 0)
		*(char *)(return_ptr + allocation_size) = '\0';
	return (return_ptr);
}
