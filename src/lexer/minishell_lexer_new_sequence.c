/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_new_sequence.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:34:33 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 05:27:20 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

int	word_add_char(char **input, t_token **new_token)
{
	t_char_list	*next_char;

	next_char = char_list_create(**input);
	if (!(next_char))
		return (ENOMEM);
	char_list_add(&(*new_token)->word, next_char);
	return (0);
}

static int	set_next_state(char **input,
		int *state, t_token **new_token)
{
	if (**input == '<')
		*state += INPUT_REDIRECTION - NEW_SEQUENCE;
	else if (**input == '>')
		*state += OUTPUT_REDIRECTION - NEW_SEQUENCE;
	else if (**input == '(')
	{
		(*new_token)->type = OPEN_PARENTHESIS;
		*state += COMPLETED_TOKEN;
	}
	else if (**input)
	{
		*state += COMMAND - NEW_SEQUENCE;
		if (word_add_char(input, new_token))
			return (ENOMEM);
	}
	if ((*new_token)->type != OPEN_PARENTHESIS)
		(*new_token)->type = *state & MAIN_STATE;
	return (0);
}

void	set_auxiliary_state(char **input,
		int *state)
{
	static long	last_input;

	if (input == RESET)
	{
		last_input = 0;
		return ;
	}
	if (last_input == (long)*input)
		return ;
	if (((!(*state & SINGLE_QUOTES)) && **input == '\"')
		|| ((*state & DOUBLE_QUOTES) && **input == '\"'))
		*state ^= DOUBLE_QUOTES;
	else if (((!(*state & DOUBLE_QUOTES)) && **input == '\'')
		|| ((*state & SINGLE_QUOTES) && **input == '\''))
		*state ^= SINGLE_QUOTES;
	else if (!(*state & QUOTES))
	{
		if (**input == '(')
			*state |= OPEN_PARENTHESIS;
		else if (**input == ')')
			*state ^= (OPEN_PARENTHESIS + CLOSE_PARENTHESIS);
	}
	last_input = (long)*input;
}

int	new_sequence_lexer(char **input,
		int *state, t_token **token_list, t_token **new_token)
{
	(void)token_list;
	if (!(*state & QUOTES))
		skip_spaces(input);
	if (!(**input))
		return (0);
	if (verify_syntax(input, *state,
			*new_token, NEW_SEQUENCE_SYNTAX_MASK))
		return (SYNTAX_ERROR);
	if (set_next_state(input, state, new_token))
		return (ENOMEM);
	*state |= NO_COMMAND;
	set_auxiliary_state(input, state);
	(*input)++;
	if (!(*state & QUOTES))
		skip_spaces(input);
	return (0);
}
