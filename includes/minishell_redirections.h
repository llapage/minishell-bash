/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:38:01 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 09:54:46 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_REDIRECTIONS_H
# define MINISHELL_REDIRECTIONS_H

# include <fcntl.h>
# include "minishell_ast.h"
# include "minishell_errors.h"
# include "minishell_pipes.h"

void	set_redirections(t_ast *node);
void	handle_pipe_infiles(t_ast *node);
void	handle_pipe_outfiles(t_ast *node);
void	open_files(t_ast *node, t_arg_list **arg_ptr, char *path);

#endif
