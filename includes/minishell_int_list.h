/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:18:00 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:48:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INT_LIST_H
# define MINISHELL_INT_LIST_H

# include <stdlib.h>
# include <stddef.h>
# include <errno.h>
# include "../dep/libft/libft.h"

typedef struct s_int_list
{
	int					data;
	struct s_int_list	*next;
}	t_int_list;

t_int_list	*int_list_create(int data);
void		int_list_clear(t_int_list **head);
void		int_list_add(t_int_list **head, t_int_list *new_node);
int			int_list_print(t_int_list *head);
int			*int_list_to_int_array(t_int_list *head);
size_t		*int_list_to_size_t_array(t_int_list *head);

#endif
