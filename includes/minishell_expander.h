/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:32:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 22:00:48 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXPANDER_H
# define MINISHELL_EXPANDER_H

# include "minishell_parser.h"
# include "minishell_builtins.h"
# include "minishell_char_list.h"
# include "minishell_environment.h"
# include "minishell_ast.h"

void	expander(t_ast *node, t_arg_list **args, int mode);
int		expand_exit_code(t_char_list **char_list, char *root_dir);
int		wildcard_expander(t_ast *node, t_arg_list **args, t_char_list *pattern,
			int *match);
char	**arg_list_to_argv(t_arg_list *arg_list);
int		arg_list_to_argc(t_arg_list *arg_list);
int		char_list_to_env_value(t_char_list *env_var_start, size_t env_var_len,
			char **env_key, char **env);
int		char_list_env_expand(t_char_list **char_list,
			t_char_list *env_var_start, size_t env_var_len, char **env);
int		pattern_match(char *string, t_char_list *pattern,
			t_char_list *prev_pattern);
char	**get_dir_array(char *cwd);

#endif
