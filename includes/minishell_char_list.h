/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_char_list.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:18:00 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 20:16:13 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CHAR_LIST_H
# define MINISHELL_CHAR_LIST_H

# include <stddef.h>
# include <stdlib.h>
# include <errno.h>
# include "../dep/libft/libft.h"

typedef struct s_char_list
{
	char				character;
	int					is_wildcard;
	struct s_char_list	*next;
}	t_char_list;

t_char_list	*char_list_create(char character);
t_char_list	*char_list_copy(t_char_list *src_char_list);
void		char_list_clear(t_char_list **lst);
size_t		char_list_len(t_char_list *lst);
void		char_list_add(t_char_list **char_list, t_char_list *new_char);
int			char_list_remove(t_char_list **char_list, t_char_list **char_ptr);
t_char_list	*char_list_remove_range(t_char_list **char_list,
				t_char_list *env_var_start, size_t env_var_len);
void		char_list_remove_last_dir(t_char_list **char_list);
int			char_list_insert_str(t_char_list **char_list,
				t_char_list *insert_ptr, char *str);
int			char_list_chr(t_char_list *char_list, char character);
char		*char_list_to_str(t_char_list *char_list);
int			char_list_print(t_char_list *char_list);
t_char_list	*str_to_char_list(char *str);
int			char_list_contains_space(t_char_list *char_list);

#endif
