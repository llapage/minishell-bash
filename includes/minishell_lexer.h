/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 07:48:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 23:17:08 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_LEXER_H
# define MINISHELL_LEXER_H

# define RESET 0

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include "minishell_token.h"
# include "minishell_definitions.h"
# include "minishell_errors.h"
# include "../dep/libft/libft.h"

int		lexer(char *input, t_token **tokens);
int		new_sequence_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		command_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		new_argument_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		argument_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		input_redirection_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		output_redirection_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		output_append_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		logical_and_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		pipe_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
int		heredoc_lexer(char **input, int *state, t_token **tokens,
			t_token **new_token);
void	set_auxiliary_state(char **input, int *state);
int		add_completed_token(t_token **tokens, t_token **new_token, int *state);
int		verify_syntax(char **input, int state, t_token *new_token,
			int error_mask);
int		verify_syntax_2(char **input, int state, t_token *new_token,
			int error_mask);
int		verify_syntax_3(char **input, int state, t_token *token,
			int error_mask);
int		is_redirection(int state);
int		word_add_char(char **input, t_token **new_token);
int		is_metachar(char c);
void	lexer_fail(char *input);
void	lexer_add_token_fail(char *input, t_token *new_token, t_token *tokens);
int		lexer_function_fail(char *input, t_token *new_token, t_token *tokens,
			int ret);

#endif
