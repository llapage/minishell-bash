/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_arg_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:49:25 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 18:01:46 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ARG_LIST_H
# define MINISHELL_ARG_LIST_H

# include <errno.h>
# include "minishell_char_list.h"
# include "../dep/libft/libft.h"

typedef struct s_arg_list
{
	t_char_list			*arg;
	int					mode;
	int					split;
	int					empty;
	struct s_arg_list	*next;
}	t_arg_list;

int		arg_list_add(t_arg_list **args, t_char_list *arg);
void	arg_list_remove(t_arg_list **args, t_arg_list *arg);
void	arg_list_clear(t_arg_list **head);
int		arg_list_insert(t_arg_list **args, t_arg_list *ptr, t_char_list *arg);
int		arg_list_print(t_arg_list *head);
size_t	arg_list_len(t_arg_list *arg);
char	**arg_list_to_str_arr(t_arg_list *arg_list);

#endif
