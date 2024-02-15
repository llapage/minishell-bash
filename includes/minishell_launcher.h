/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:48:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 10:11:57 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LAUNCHER_H
# define MINISHELL_LAUNCHER_H

# include "minishell_quotes.h"
# include "minishell_expander.h"
# include "minishell_builtins.h"
# include "minishell_redirections.h"
# include "minishell_errors.h"
# include <sys/types.h>
# include <sys/stat.h>

void	launcher(t_ast *node);
char	*get_path_location(char *command, t_char_list *command_node, char **env,
			t_ast *node);
void	split_args(t_ast *node);
void	no_path_var_handler(t_ast *node);
void	verify_command(t_ast *node);
void	prelim_checks(t_ast *node);

#endif
