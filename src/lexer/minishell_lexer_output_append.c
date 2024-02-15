/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_output_append.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:18:12 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 17:15:47 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (!(*state & QUOTES))
	{
		if (is_metachar(**input))
		{
			*state += NEW_ARGUMENT - OUTPUT_APPEND
				+ COMPLETED_TOKEN;
			(*input)--;
		}
		else if (word_add_char(input, new_token))
			return (ENOMEM);
		return (0);
	}
	else if (word_add_char(input, new_token))
		return (ENOMEM);
	return (0);
}

int	output_append_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	int	ret;

	(void)token_list;
	if (!(*new_token)->word)
		skip_spaces(input);
	ret = verify_syntax(input, *state, *new_token,
			OUTPUT_APPEND_SYNTAX_MASK);
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
