/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_char_list_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:16:46 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 11:46:02 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_char_list.h"

void	char_list_add(t_char_list **char_list, t_char_list *new_char)
{
	t_char_list	*lst_ptr;

	if (*char_list)
	{
		lst_ptr = *char_list;
		while (lst_ptr && lst_ptr->next)
			lst_ptr = lst_ptr->next;
		lst_ptr->next = new_char;
	}
	else
		*char_list = new_char;
}

int	char_list_remove(t_char_list **char_list,
		t_char_list **char_ptr)
{
	t_char_list	*char_list_ptr;

	if (!(*char_ptr))
		return (0);
	if (*char_list == *char_ptr)
	{
		*char_list = (*char_list)->next;
		free (*char_ptr);
		*char_ptr = *char_list;
		return (0);
	}
	char_list_ptr = *char_list;
	while (char_list_ptr && char_list_ptr->next != *char_ptr)
		char_list_ptr = char_list_ptr->next;
	char_list_ptr->next = (*char_ptr)->next;
	free(*char_ptr);
	*char_ptr = char_list_ptr->next;
	return (0);
}

void	char_list_remove_last_dir(t_char_list **char_list)
{
	t_char_list	*char_ptr;
	t_char_list	*last_char_to_keep;

	if ((!(char_list)) || (!(*char_list)->next))
		return ;
	char_ptr = *char_list;
	last_char_to_keep = *char_list;
	while (char_ptr)
	{
		if (char_ptr->next
			&& char_ptr->next->next
			&& char_ptr->next->character == '/')
			last_char_to_keep = char_ptr;
		char_ptr = char_ptr->next;
	}
	char_ptr = last_char_to_keep->next;
	last_char_to_keep->next = NULL;
	char_list_clear(&char_ptr);
}

int	char_list_insert_str(t_char_list **char_list,
		t_char_list *insert_ptr,
		char *str)
{
	t_char_list	*tmp;
	size_t		index;

	index = 0;
	while (str && str[index])
	{
		tmp = char_list_create(str[index]);
		if (!(tmp))
			return (1);
		if (!(insert_ptr))
		{
			tmp->next = *char_list;
			*char_list = tmp;
			insert_ptr = *char_list;
		}
		else
		{
			tmp->next = insert_ptr->next;
			insert_ptr->next = tmp;
			insert_ptr = insert_ptr->next;
		}
		index++;
	}
	return (0);
}

int	char_list_chr(t_char_list *char_list, char character)
{
	t_char_list	*char_ptr;

	char_ptr = char_list;
	while (char_ptr)
	{
		if (char_ptr->character == character)
			return (1);
		char_ptr = char_ptr->next;
	}
	return (0);
}
