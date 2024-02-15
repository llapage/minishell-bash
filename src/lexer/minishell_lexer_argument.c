/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_argument.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:46:02 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/26 17:54:21 by mde-clee         ###   ########.fr       */
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
			*state += NEW_ARGUMENT - ARGUMENT + COMPLETED_TOKEN;
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

int	argument_lexer(char **input,
		int *state,
		t_token **token_list,
		t_token **new_token)
{
	(void)token_list;
	if (verify_syntax(input, *state,
			*new_token, ARGUMENT_SYNTAX_MASK))
		return (SYNTAX_ERROR);
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	set_auxiliary_state(input, state);
	(*input)++;
	return (0);
}
