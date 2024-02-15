/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:21:14 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 17:12:57 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PIPES_H
# define MINISHELL_PIPES_H

# include "minishell_int_list.h"
# include "minishell_builtins.h"
# include "minishell_ast.h"

int		create_pipes(t_ast *node, t_int_list **pipe_list);
void	link_pipe_list(t_ast *node, t_int_list *pipe_list);
void	duplicate_pipes(t_ast *node);
int		close_pipes(t_int_list *pipe_list);
void	launcher_fail(t_ast *root_node, char *msg_part_1,
			char *msg_part_2, int exit_code);

#endif
