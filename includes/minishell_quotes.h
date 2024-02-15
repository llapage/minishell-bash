/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:13:27 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 18:50:29 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_QUOTES_H
# define MINISHELL_QUOTES_H

# include "minishell_ast.h"
# include "minishell_expander.h"
# include "minishell_char_list.h"

void		resolve_all_quotes(t_ast *node);
int			resolve_double_quotes(t_char_list **char_list,
				t_char_list **char_ptr, char **env, char *root_dir);
void		resolve_single_quotes(t_char_list **char_list,
				t_char_list **char_ptr);
int			resolve_quotes(t_arg_list **arg_ptr,
				t_char_list **char_list, t_ast *node, int *mode);
int			resolve_infiles_outfiles_quotes(t_ast *node, t_arg_list *arg_ptr);
int			resolve_no_quotes_var_sub(t_char_list **char_ptr,
				t_char_list **char_list, char *root_dir);
int			is_valid_char(char c);
int			resolve_exit_code(t_char_list **char_list, t_char_list **char_ptr,
				char *root_dir);
int			expand_env_var(t_char_list **char_list, t_char_list **char_ptr,
				char *root_dir, char **env);
int			expand_env_var_2(t_char_list **env_var_start, size_t *env_var_len,
				t_char_list **char_list, t_char_list **char_ptr);
int			resolve_double_quotes_2(char **env, t_char_list **char_list,
				t_char_list **char_ptr);
void		set_wildcard(t_char_list **char_ptr);
int			quotes_return_failure(void);
int			to_absolute_path_5(char **path, t_char_list **next_char,
				t_char_list **abs_path);
char		*resolve_heredoc_delimiter(t_char_list **word);

#endif
