/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_logical_and.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 12:34:59 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/13 14:35:59 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

int	logical_and_lexer(char **input,
		int *state, t_token **token_list,
		t_token **new_token)
{
	char	*wrong_char;

	(void)token_list;
	(void)new_token;
	if (**input != '&')
	{
		wrong_char = malloc(4 * sizeof(char));
		if (!(wrong_char))
			return (ENOMEM);
		wrong_char[0] = '\'';
		wrong_char[1] = '&';
		wrong_char[2] = '\'';
		wrong_char[3] = '\0';
		print_error(SYNTAX_PREFIX, NULL, wrong_char);
		free(wrong_char);
		return (SYNTAX_ERROR);
	}
	*state += NEW_SEQUENCE - LOGICAL_AND + COMPLETED_TOKEN;
	(*input)++;
	return (0);
}
