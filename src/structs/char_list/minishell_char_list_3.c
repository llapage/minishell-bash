/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_char_list_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:16:56 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/27 10:19:08 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_char_list.h"

static void	char_list_remove_range_2(t_char_list **char_list,
		t_char_list *env_var_start, size_t env_var_len,
		t_char_list **char_ptr)
{
	t_char_list	*tmp;
	size_t		i;

	i = 0;
	if (*char_list == env_var_start)
	{
		*char_ptr = NULL;
		while (i++ < env_var_len)
			*char_list = (*char_list)->next;
	}
	else
	{
		*char_ptr = (*char_list);
		while ((*char_ptr)->next != env_var_start)
			*char_ptr = (*char_ptr)->next;
		tmp = env_var_start;
		while (i++ < env_var_len)
			tmp = tmp->next;
		(*char_ptr)->next = tmp;
	}
}

t_char_list	*char_list_remove_range(t_char_list **char_list,
		t_char_list *env_var_start, size_t env_var_len)
{
	t_char_list	*char_ptr;
	t_char_list	*tmp;
	size_t		i;

	char_list_remove_range_2(char_list, env_var_start, env_var_len, &char_ptr);
	i = 0;
	while (i < env_var_len)
	{
		tmp = env_var_start;
		env_var_start = env_var_start->next;
		free(tmp);
		i++;
	}
	return (char_ptr);
}

static char	*char_list_to_str_2(t_char_list *lst_ptr, int len)
{
	char	*str;
	int		pos;

	str = malloc((len + 1) * sizeof(char));
	if (!(str))
	{
		errno = ENOMEM;
		return (NULL);
	}
	str[len] = '\0';
	pos = 0;
	while (pos < len)
	{
		str[pos++] = lst_ptr->character;
		lst_ptr = lst_ptr->next;
	}
	return (str);
}

char	*char_list_to_str(t_char_list *char_list)
{
	t_char_list	*lst_ptr;
	int			len;

	if (!(char_list))
		return (NULL);
	len = 1;
	lst_ptr = char_list;
	while (lst_ptr->next != NULL)
	{
		len++;
		lst_ptr = lst_ptr->next;
	}
	lst_ptr = char_list;
	return (char_list_to_str_2(lst_ptr, len));
}
