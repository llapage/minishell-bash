/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:00:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 18:51:01 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H

# define RESET 0

# include <stdio.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "minishell_token.h"
# include "minishell_ast.h"
# include "minishell_memory.h"
# include "minishell_expander.h"
# include "minishell_quotes.h"

int	parser(t_token *token_list, char *root_dir, t_ast **head, char **env);
int	heredoc_handler(char *delimiter, char **heredoc_file, char *root_dir,
		char **env);
int	handle_token(t_token *token, t_ast **node, t_ast **head, char **env);
int	handle_token_2(t_token *token, t_ast **node, int *bad_file, char **env);
int	dir_exists(char *folder);
int	heredoc_expand_input(char **input, char **env);
int	heredoc_handler_3(int fd, char *root_dir);

#endif
