/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_arg_list_to_str_arr.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:40:18 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/28 16:39:42 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_arg_list.h"

static size_t	*get_marks_array(t_arg_list *arg_list)
{
	size_t		*marks_array;
	size_t		arr_len;
	size_t		arg_len;
	t_arg_list	*arg_node_ptr;

	arr_len = arg_list_len(arg_list);
	marks_array = malloc((arr_len + 1) * sizeof(size_t));
	if (!(marks_array))
	{
		errno = ENOMEM;
		return (NULL);
	}
	marks_array[0] = arr_len;
	arr_len = 1;
	arg_node_ptr = arg_list;
	while (arg_node_ptr)
	{
		arg_len = char_list_len(arg_node_ptr->arg);
		marks_array[arr_len++] = arg_len;
		arg_node_ptr = arg_node_ptr->next;
	}
	return (marks_array);
}

static int	get_long_string_2(t_arg_list **arg_list_ptr, char **long_string)
{
	char		*next_arg;

	*arg_list_ptr = (*arg_list_ptr)->next;
	errno = 0;
	next_arg = char_list_to_str((*arg_list_ptr)->arg);
	if ((!(next_arg)) && errno == ENOMEM)
	{
		free(*long_string);
		return (-1);
	}
	*long_string = ft_strfjoin(*long_string, next_arg);
	free (next_arg);
	if (!(*long_string))
	{
		errno = ENOMEM;
		return (-1);
	}
	return (0);
}

static char	*get_long_string(t_arg_list *arg_list)
{
	char		*long_string;
	t_arg_list	*arg_list_ptr;

	arg_list_ptr = arg_list;
	errno = 0;
	long_string = char_list_to_str(arg_list_ptr->arg);
	if ((!(long_string)) && errno == ENOMEM)
		return (NULL);
	while (arg_list_ptr->next)
		if (get_long_string_2(&arg_list_ptr, &long_string))
			return (NULL);
	return (long_string);
}

char	**arg_list_to_str_arr(t_arg_list *arg_list)
{
	char	*long_string;
	size_t	*marks_array;
	char	**str_arr;

	if (!(arg_list))
		return (NULL);
	long_string = get_long_string(arg_list);
	if (!(long_string))
		return (NULL);
	marks_array = get_marks_array(arg_list);
	if (!(marks_array))
	{
		free(long_string);
		return (NULL);
	}
	str_arr = ft_csplit(long_string, marks_array);
	free(long_string);
	free(marks_array);
	if (!(str_arr))
		errno = ENOMEM;
	return (str_arr);
}
