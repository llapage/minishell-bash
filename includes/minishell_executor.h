/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 07:48:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 10:02:16 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTOR_H
# define MINISHELL_EXECUTOR_H

# ifndef __APPLE__
#  define __APPLE__ 0
# endif

# include "minishell_environment.h"
# include "minishell_pipes.h"
# include "minishell_builtins.h"
# include "minishell_launcher.h"
# include "minishell_signals.h"
# include <sys/wait.h>

int		executor(t_ast *command_node, char **env, char *root);
void	executor_main(t_ast *command_node);
void	leaf_node_handler(t_ast *node);
void	pipe_node_handler(t_ast *node);
void	and_or_node_handler(t_ast *node);
void	subshell_node_handler(t_ast *node);

#endif
