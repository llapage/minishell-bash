/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_input_redirection.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:18:12 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 17:14:47 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static void	set_next_state_no_quotes_2(char **input, int *state)
{
	*state += NEW_ARGUMENT - INPUT_REDIRECTION
		+ COMPLETED_TOKEN;
	(*input)--;
}

static int	set_next_state_no_quotes(char **input,
		int *state, t_token **new_token)
{
	if (**input == '<')
	{
		if (!(*new_token)->word)
		{
			*state += HEREDOC - INPUT_REDIRECTION;
			(*new_token)->type += HEREDOC - INPUT_REDIRECTION;
		}
		else
		{
			*state += NEW_SEQUENCE - INPUT_REDIRECTION + COMPLETED_TOKEN;
			(*input)--;
		}
	}
	else if (is_metachar(**input))
		set_next_state_no_quotes_2(input, state);
	else if (word_add_char(input, new_token))
		return (ENOMEM);
	return (0);
}

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (!(*state & QUOTES))
		return (set_next_state_no_quotes(input, state, new_token));
	else if (word_add_char(input, new_token))
		return (ENOMEM);
	return (0);
}

int	input_redirection_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	int	ret;

	(void)token_list;
	if (!(*new_token)->word)
		skip_spaces(input);
	if (!(*state & QUOTES))
	{
		ret = verify_syntax(input, *state, *new_token,
				INPUT_REDIRECTION_SYNTAX_MASK);
		if (ret)
		{
			if (ret == SYSTEM_FAILURE)
				return (SYSTEM_FAILURE);
			return (SYNTAX_ERROR);
		}
	}
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	set_auxiliary_state(input, state);
	(*input)++;
	return (0);
}
