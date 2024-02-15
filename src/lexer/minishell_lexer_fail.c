/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_fail.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:25:21 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/26 17:51:00 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

void	lexer_fail(char *input)
{
	free(input);
	print_error(PREFIX, NULL, STRERROR);
	exit(EXIT_FAILURE);
}

void	lexer_add_token_fail(char *input, t_token *new_token, t_token *tokens)
{
	token_clear(new_token);
	token_clear(tokens);
	lexer_fail(input);
}

int	lexer_function_fail(char *input, t_token *new_token,
		t_token *tokens, int ret)
{
	token_clear(new_token);
	token_clear(tokens);
	if (ret == ENOMEM)
		lexer_fail(input);
	if (ret == SYNTAX_ERROR)
		return (258);
	else if (ret == SYSTEM_FAILURE)
		return (SYSTEM_FAILURE);
	return (1);
}
