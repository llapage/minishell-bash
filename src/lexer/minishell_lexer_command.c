/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:23:38 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 15:27:18 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

int	is_metachar(char c)
{
	if (c == ' '
		|| c == '<'
		|| c == '>'
		|| c == '&'
		|| c == '|'
		|| c == '('
		|| c == ')'
		|| (c > 8 && c < 14))
		return (1);
	return (0);
}

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (!(*state & QUOTES))
	{
		if (is_metachar(**input))
		{
			*state += NEW_ARGUMENT - COMMAND
				- NO_COMMAND + COMPLETED_TOKEN;
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

int	command_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	(void)token_list;
	if (verify_syntax(input, *state, *new_token, COMMAND_SYNTAX_MASK))
		return (SYNTAX_ERROR);
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	set_auxiliary_state(input, state);
	(*input)++;
	return (0);
}
