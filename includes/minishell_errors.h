/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 05:17:49 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 06:37:23 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERRORS_H
# define MINISHELL_ERRORS_H

# define STRERROR 0
# define PREFIX "Minishell: "
# define SYNTAX_PREFIX "Minishell: syntax error near unexpected token "
# define NO_PREFIX ""
# define SYNTAX_ERROR 1
# define SYSTEM_FAILURE -3

# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "../dep/libft/libft.h"
# include "minishell_definitions.h"
# include "minishell_ast.h"

int		print_error(char *prefix, char *command_or_file, char *err_msg);
int		error_enomem(int code, char *msg, void *ptr);
void	exit_malloc_fail(t_ast *root_node);
void	free_and_exit(t_ast *root_node, int exit_code);
void	launcher_fail(t_ast *root_node, char *msg_part_1,
			char *msg_part_2, int exit_code);
void	free_exit_malloc_fail(t_ast *root_node, char *file);
void	pipe_fail(t_ast *root_node, char *msg_part_1,
			char *msg_part_2, int exit_code);

#endif
