/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:51:19 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/27 09:37:29 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static int	good_input(char **input, int *state, t_token **new_token)
{
	skip_spaces(input);
	if (**input == '|')
	{
		*state &= ~(CLOSE_PARENTHESIS);
		return (1);
	}
	else if (**input == '&')
	{
		(*new_token)->type = LOGICAL_AND;
		*state += LOGICAL_AND - PIPE;
		*state &= ~(CLOSE_PARENTHESIS);
		return (1);
	}
	else if (**input == ')')
	{
		(*new_token)->type = CLOSE_PARENTHESIS;
		*state += COMPLETED_TOKEN;
		return (1);
	}
	return (0);
}

static void	pipe_lexer_2(char **input, int *state, t_token **new_token)
{
	if (**input == '|')
	{
		(*new_token)->type = LOGICAL_OR;
		(*input)++;
	}
	*state += NEW_SEQUENCE - PIPE + COMPLETED_TOKEN;
}

int	pipe_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	char	*wrong_char;

	(void)token_list;
	if (*state & CLOSE_PARENTHESIS)
	{
		if (!(good_input(input, state, new_token)))
		{
			wrong_char = malloc(4 * sizeof(char));
			if (!(wrong_char))
				return (ENOMEM);
			wrong_char[0] = '\'';
			wrong_char[1] = **input;
			wrong_char[2] = '\'';
			wrong_char[3] = '\0';
			print_error(SYNTAX_PREFIX, NULL, wrong_char);
			free(wrong_char);
			return (SYNTAX_ERROR);
		}
		(*input)++;
	}
	else
		pipe_lexer_2(input, state, new_token);
	return (0);
}
