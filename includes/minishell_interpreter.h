/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:57:09 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 15:21:34 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INTERPRETER_H
# define MINISHELL_INTERPRETER_H

# define INPUT 0
# define OUTPUT 1

# ifndef __APPLE__
#  define __APPLE__ 0
# endif

# include "minishell_ast.h"
# include "minishell_errors.h"
# include "minishell_memory.h"

int	interpreter(t_ast **raw_nodes);
int	interpret_operator_node(t_ast **stacked_nodes, t_ast **symbol_nodes,
		t_ast **command_nodes);
int	interpret_end_subshell_node(t_ast **stacked_nodes, t_ast **symbol_nodes,
		t_ast **command_nodes);
int	link_nodes(t_ast *node, t_ast *right, t_ast *left, t_ast **command_nodes);

#endif
