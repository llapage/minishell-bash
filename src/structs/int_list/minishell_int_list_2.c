/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int_list_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:24:08 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 19:27:10 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_int_list.h"

static int	*int_list_to_int_array_2(t_int_list *head, int *int_array,
		size_t size, t_int_list *int_ptr)
{
	int_array[0] = size;
	int_ptr = head;
	size = 0;
	while (int_ptr)
	{
		int_array[size++] = int_ptr->data;
		int_ptr = int_ptr->next;
	}
	return (int_array);
}

int	*int_list_to_int_array(t_int_list *head)
{
	t_int_list	*int_ptr;
	size_t		size;
	int			*int_array;

	size = 0;
	int_ptr = head;
	while (int_ptr)
	{
		size++;
		int_ptr = int_ptr->next;
	}
	int_array = malloc((size + 1) * sizeof(int));
	if (!(int_array))
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (int_list_to_int_array_2(head, int_array, size, int_ptr));
}

static size_t	*int_list_to_size_t_array_2(t_int_list *head,
		size_t *size_t_array, size_t size, t_int_list *int_ptr)
{
	size_t_array[0] = size;
	int_ptr = head;
	size = 1;
	while (int_ptr)
	{
		size_t_array[size++] = (size_t)int_ptr->data;
		int_ptr = int_ptr->next;
	}
	return (size_t_array);
}

size_t	*int_list_to_size_t_array(t_int_list *head)
{
	t_int_list	*int_ptr;
	size_t		size;
	size_t		*size_t_array;

	size = 0;
	int_ptr = head;
	while (int_ptr)
	{
		size++;
		int_ptr = int_ptr->next;
	}
	size_t_array = malloc((size + 1) * sizeof(size_t));
	if (!(size_t_array))
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (int_list_to_size_t_array_2(head, size_t_array, size, int_ptr));
}
