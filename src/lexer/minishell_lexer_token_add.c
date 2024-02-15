/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_token_add.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:41:37 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 15:52:09 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

static int	disregard_token(t_token **new_token, int *state)
{
	(*new_token)->type = *state & MAIN_STATE;
	*state -= COMPLETED_TOKEN;
	return (0);
}

static int	add_close_parenthesis_token(t_token **tokens,
		int state, t_token *ready_token)
{
	t_token	*close_parenthesis_token;

	if (state & CLOSE_PARENTHESIS
		&& (!(ready_token->type == CLOSE_PARENTHESIS)))
	{
		close_parenthesis_token = token_create(CLOSE_PARENTHESIS);
		if (!(close_parenthesis_token))
			return (ENOMEM);
		token_add(tokens, close_parenthesis_token);
	}
	return (0);
}

int	add_completed_token(t_token **tokens, t_token **new_token, int *state)
{
	t_token	*ready_token;

	if ((*new_token)->type == NEW_ARGUMENT)
		return (disregard_token(new_token, state));
	ready_token = token_copy(*new_token);
	if (!(ready_token))
		return (ENOMEM);
	ready_token->root_dir = NULL;
	token_add(tokens, ready_token);
	(*new_token)->type = *state & MAIN_STATE;
	char_list_clear(&(*new_token)->word);
	if (add_close_parenthesis_token(tokens, *state, ready_token))
		return (ENOMEM);
	*state &= ~(COMPLETED_TOKEN);
	return (0);
}
