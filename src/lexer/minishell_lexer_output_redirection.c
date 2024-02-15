/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_output_redirection.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:18:12 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 17:10:10 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static int	set_next_state_2(char **input,
		int *state, t_token **new_token)
{
	if (**input == '>')
	{
		if (!(*new_token)->word)
		{
			*state += OUTPUT_APPEND - OUTPUT_REDIRECTION;
			(*new_token)->type += OUTPUT_APPEND - OUTPUT_REDIRECTION;
		}
		else
		{
			*state += NEW_SEQUENCE - OUTPUT_REDIRECTION + COMPLETED_TOKEN;
			(*input)--;
		}
		return (1);
	}
	else if (is_metachar(**input))
	{
		*state += NEW_ARGUMENT - OUTPUT_REDIRECTION + COMPLETED_TOKEN;
		(*input)--;
		return (1);
	}
	return (0);
}

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (!(*state & QUOTES))
	{
		if (set_next_state_2(input, state, new_token))
			;
		else if (word_add_char(input, new_token))
			return (ENOMEM);
		return (0);
	}
	else if (word_add_char(input, new_token))
		return (ENOMEM);
	return (0);
}

int	output_redirection_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	int	ret;

	(void)token_list;
	if (!(*new_token)->word)
		skip_spaces(input);
	ret = verify_syntax(input, *state, *new_token,
			OUTPUT_REDIRECTION_SYNTAX_MASK);
	if (ret)
	{
		if (ret == SYSTEM_FAILURE)
			return (SYSTEM_FAILURE);
		return (SYNTAX_ERROR);
	}
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	set_auxiliary_state(input, state);
	(*input)++;
	return (0);
}
