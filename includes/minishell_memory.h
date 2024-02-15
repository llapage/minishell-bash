/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_memory.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:58:02 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 20:17:52 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MEMORY_H
# define MINISHELL_MEMORY_H

# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <dirent.h>
# include "../dep/libft/libft.h"
# include "minishell_token.h"
# include "minishell_ast.h"

int	g_exit_code;

void	free_strstr(char ***strstr, size_t len);
int		clear_cache(char *root_dir);
int		clear_subshell_cache(char *root_dir);
void	free_tokens(t_token *head);
void	free_node(t_ast *node);
void	free_tree(t_ast *node);
void	free_tree2(t_ast *node);
void	free_stacked_nodes(t_ast *stacked_nodes, t_ast *symbol_nodes,
			t_ast *command_nodes);
int		free_ret_1(char *str);

#endif
