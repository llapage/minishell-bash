/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_new_argument.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:55:35 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 16:34:31 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (**input == '<')
		*state += INPUT_REDIRECTION - NEW_ARGUMENT + COMPLETED_TOKEN;
	else if (**input == '>')
		*state += OUTPUT_REDIRECTION - NEW_ARGUMENT + COMPLETED_TOKEN;
	else if (**input == '&')
		*state += LOGICAL_AND - NEW_ARGUMENT + COMPLETED_TOKEN;
	else if (**input == '|')
		*state += PIPE - NEW_ARGUMENT + COMPLETED_TOKEN;
	else if (**input == ')')
	{
		*state += PIPE - NEW_ARGUMENT + COMPLETED_TOKEN;
		(*new_token)->type = CLOSE_PARENTHESIS;
	}
	else if (**input)
	{
		(*new_token)->type = ARGUMENT;
		if (word_add_char(input, new_token))
			return (ENOMEM);
		*state += ARGUMENT - NEW_ARGUMENT;
	}
	return (0);
}

int	new_argument_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	(void)token_list;
	skip_spaces(input);
	if (!(**input))
		return (0);
	if (verify_syntax(input, *state,
			*new_token, NEW_ARGUMENT_SYNTAX_MASK))
		return (SYNTAX_ERROR);
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	set_auxiliary_state(input, state);
	(*input)++;
	return (0);
}
