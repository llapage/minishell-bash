/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_char_list_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:16:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 17:57:40 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_char_list.h"

t_char_list	*char_list_create(char character)
{
	t_char_list	*new_char;

	new_char = malloc(sizeof(t_char_list));
	if (!(new_char))
	{
		errno = ENOMEM;
		return (NULL);
	}
	new_char->character = character;
	new_char->next = NULL;
	return (new_char);
}

t_char_list	*char_list_copy(t_char_list *src_char_list)
{
	t_char_list	*char_list_copy;
	t_char_list	*next_char_node;
	t_char_list	*src_list_ptr;

	if (!(src_char_list))
		return (NULL);
	char_list_copy = NULL;
	src_list_ptr = src_char_list;
	while (src_list_ptr)
	{
		next_char_node = char_list_create(src_list_ptr->character);
		if (!(next_char_node))
			return (NULL);
		char_list_add(&char_list_copy, next_char_node);
		src_list_ptr = src_list_ptr->next;
	}
	return (char_list_copy);
}

void	char_list_clear(t_char_list **lst)
{
	t_char_list	*next_ptr;
	t_char_list	*lst_ptr;

	lst_ptr = *lst;
	while (lst_ptr)
	{
		next_ptr = lst_ptr->next;
		free(lst_ptr);
		lst_ptr = NULL;
		lst_ptr = next_ptr;
	}
	*lst = NULL;
}

size_t	char_list_len(t_char_list *lst)
{
	t_char_list	*node_ptr;
	size_t		len;

	node_ptr = lst;
	len = 0;
	while (node_ptr)
	{
		len++;
		node_ptr = node_ptr->next;
	}
	return (len);
}

int	char_list_print(t_char_list *char_list)
{
	t_char_list	*char_ptr;

	char_ptr = char_list;
	while (char_ptr)
	{
		if (ft_pputchar_fd(char_ptr->character, 1) == -1)
			return (-1);
		char_ptr = char_ptr->next;
	}
	return (0);
}
