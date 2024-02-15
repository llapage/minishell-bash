/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_char_list_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:14:44 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 20:14:09 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_char_list.h"

int	char_list_contains_space(t_char_list *char_list)
{
	t_char_list	*ptr;

	ptr = char_list;
	while (ptr)
	{
		if (ft_isspace(ptr->character))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static t_char_list	*malloc_fail(void)
{
	errno = ENOMEM;
	return (NULL);
}

t_char_list	*str_to_char_list(char *str)
{
	t_char_list	*char_list_head;
	t_char_list	*char_list_ptr;

	if (!(*str))
		return (NULL);
	char_list_head = malloc(sizeof(t_char_list));
	if (!(char_list_head))
		return (malloc_fail());
	char_list_head->character = *str++;
	char_list_head->next = NULL;
	char_list_ptr = char_list_head;
	while (*str)
	{
		char_list_ptr->next = char_list_create(*str++);
		if (!(char_list_ptr))
		{
			char_list_clear(&char_list_head);
			return (malloc_fail());
		}
		char_list_ptr = char_list_ptr->next;
	}
	return (char_list_head);
}
