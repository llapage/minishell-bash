/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_finalizer.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:47:21 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 14:31:13 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FINALIZER_H
# define MINISHELL_FINALIZER_H

# include "minishell_ast.h"
# include "minishell_pipes.h"

int	finalizer(t_ast *nodes, char *root_dir);
int	set_various(t_ast *root_node, t_ast *node, int shell_id, char *root_dir);

#endif
