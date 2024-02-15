/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:52:04 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 16:22:12 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENVIRONMENT_H
# define MINISHELL_ENVIRONMENT_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../dep/libft/libft.h"
# include "minishell_ast.h"
# include "minishell_builtins.h"
# include "minishell_file.h"
# include "minishell_memory.h"
# include "minishell_errors.h"

int		env_to_file(char **env, char *env_file);
int		create_env_file(char **env, char *root);
int		get_env_file(t_ast *node);
int		copy_parent_shell_env_file(t_ast *node, int env_fd);
int		expand_env_file(t_ast *node);
char	*ft_getenv(char *key, char **env);
int		print_env(char **env);
int		print_env_export(char **env);

#endif
