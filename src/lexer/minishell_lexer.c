/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:58:15 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 19:57:20 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static void	init_lexer_functions(
		int (*lexer_functions[11])(
			char **input_ptr,
			int *status,
			t_token **tokens,
			t_token **new_token))
{
	lexer_functions[NEW_SEQUENCE] = &new_sequence_lexer;
	lexer_functions[COMMAND] = &command_lexer;
	lexer_functions[NEW_ARGUMENT] = &new_argument_lexer;
	lexer_functions[ARGUMENT] = &argument_lexer;
	lexer_functions[INPUT_REDIRECTION] = &input_redirection_lexer;
	lexer_functions[OUTPUT_REDIRECTION] = &output_redirection_lexer;
	lexer_functions[OUTPUT_APPEND] = &output_append_lexer;
	lexer_functions[LOGICAL_AND] = &logical_and_lexer;
	lexer_functions[PIPE] = &pipe_lexer;
	lexer_functions[HEREDOC] = &heredoc_lexer;
}

static void	init_lexer(char *input, t_token **tokens, t_token **new_token,
		int *state)
{
	set_auxiliary_state(RESET, NULL);
	*tokens = NULL;
	*state = NEW_SEQUENCE;
	*new_token = token_create(*state);
	if (!(*new_token))
		lexer_fail(input);
}

static int	lexer_verify_syntax(t_token *tokens, t_token *new_token, int state)
{
	if (state & QUOTES || ((is_redirection(state)
				|| (((state & MAIN_STATE) == PIPE)
					&& (!(state & CLOSE_PARENTHESIS)))
				|| (((state & MAIN_STATE) == LOGICAL_AND)
					&& (!(state & CLOSE_PARENTHESIS))))
			&& (!(new_token->word))))
	{
		print_error(SYNTAX_PREFIX, NULL, "`newline'");
		token_clear(new_token);
		token_clear(tokens);
		return (258);
	}
	return (0);
}

int	lexer(char *input, t_token **tokens)
{
	int		state;
	t_token	*new_token;
	char	*input_ptr;
	int		(*lexer_functions[11])(char **, int *, t_token **, t_token **);
	int		ret;

	init_lexer_functions(lexer_functions);
	init_lexer(input, tokens, &new_token, &state);
	input_ptr = input;
	while (*input_ptr)
	{
		if (state & COMPLETED_TOKEN
			&& add_completed_token(tokens, &new_token, &state))
			lexer_add_token_fail(input, new_token, *tokens);
		ret = lexer_functions[state & MAIN_STATE]
			(&input_ptr, &state, tokens, &new_token);
		if (ret)
			return (lexer_function_fail(input, new_token, *tokens, ret));
	}
	if (lexer_verify_syntax(*tokens, new_token, state))
		return (258);
	if (add_completed_token(tokens, &new_token, &state))
		lexer_add_token_fail(input, new_token, *tokens);
	free(new_token);
	return (0);
}
