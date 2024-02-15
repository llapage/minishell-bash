/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:05:22 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 11:54:14 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTINS_H
# define MINISHELL_BUILTINS_H

# define USE_FILE 0
# define USE_NEW_PWD 0

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "../dep/libft/libft.h"
# include "minishell_memory.h"
# include "minishell_environment.h"
# include "minishell_executor.h"

void	check_builtin(t_ast *node);
int		export_var(char *name, char *value, char ***env, char *env_file);
int		export_var_builtin(t_ast *node);
char	*create_line(char *name, char *value);
int		check_replace(char ***env, char *line);
char	**add_line_env(char **env, char *line);
int		export_error(char **argv);
int		strcmp_env(const char *s1, const char *s2);
char	*to_absolute_path(char *input_path, t_ast *node);
void	cd_remove_dir_path(char **path, t_char_list **next_char,
			t_char_list **abs_path);
void	cd_remove_dots(char **path);
int		unset_var(t_ast *node);
int		echo(char **argv);
int		pwd(char **env);
char	*get_cwd(char *cwd_file, char *root);
int		set_cwd(t_ast *node);
int		ch_dir(char *path, char *cwd_file, char *root);
int		exit_builtin(t_ast *node, int argc, char **argv, char *root_dir);
void	check_exit_code(t_ast *root_node, char *root_dir, int *exit_status);
void	set_exit_code(int exit_code, t_ast *root_node, char *root);
int		write_exit_code(char *exit_str, char *root);
void	free_and_exit(t_ast *node, int exit_code);
int		eof_exit(char *root_dir, int interactive_mode);
void	exit_malloc_fail(t_ast *root_node);
int		too_much_arguments(int *ret, char *root_dir);
int		is_valid(char *arg);
int		print_env_error(int mode, char *input);

#endif
