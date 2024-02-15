/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_verify_syntax.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:28:31 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 23:18:44 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

int	is_redirection(int state)
{
	if ((state & MAIN_STATE) == INPUT_REDIRECTION
		|| (state & MAIN_STATE) == OUTPUT_REDIRECTION
		|| (state & MAIN_STATE) == OUTPUT_APPEND
		|| (state & MAIN_STATE) == HEREDOC)
		return (1);
	return (0);
}

static int	verify_syntax_5(char **input)
{
	char	*tmp;
	int		ret;

	if ((!(ft_isalnum(**input))) && **input != '_'
		&& **input != '\"' && **input != '\''
		&& **input != '/'
		&& **input != '$' && (**input != *(*input - 1)))
	{
		if (**input == '*')
			return (print_error(PREFIX, "*", "ambiguous redirect"));
		tmp = malloc(sizeof(char *) * 4);
		if (!(tmp))
			return (SYSTEM_FAILURE);
		tmp[0] = '`';
		tmp[1] = **input;
		tmp[2] = '\'';
		tmp[3] = '\0';
		ret = print_error(SYNTAX_PREFIX, NULL, tmp);
		free(tmp);
		return (ret);
	}
	return (0);
}

static int	verify_syntax_4(char **input, int state, t_token *token,
		int error_mask)
{
	if (error_mask & GREATER_THAN && **input == '>' && (!(token->word)))
	{
		if (*(*input + 1) && *(*input + 1) == '>')
			return (print_error(SYNTAX_PREFIX, NULL, "`>>'"));
		else
			return (print_error(SYNTAX_PREFIX, NULL, "`>'"));
	}
	else if (error_mask & SMALLER_THAN && **input == '<')
	{
		if (*(*input + 1) && *(*input + 1) == '<')
			return (print_error(SYNTAX_PREFIX, NULL, "`<<'"));
		else
			return (print_error(SYNTAX_PREFIX, NULL, "`<'"));
	}
	else if (is_redirection(state) && (!(token->word)))
		return (verify_syntax_5(input));
	return (0);
}

int	verify_syntax_3(char **input, int state, t_token *token, int error_mask)
{
	if (error_mask & AMPERSAND && **input == '&')
	{
		if (*(*input + 1)
			&& *(*input + 1) == '&')
			return (print_error(SYNTAX_PREFIX, NULL, ("`&&'")));
		return (print_error(SYNTAX_PREFIX, NULL, ("`&'")));
	}
	else if (error_mask & WILDCARD && **input == '*')
	{
		if ((!(*(*input + 1)))
			|| *(*input + 1) == '*')
			return (print_error(SYNTAX_PREFIX, NULL, "`*'"));
	}
	else
		return (verify_syntax_4(input, state, token, error_mask));
	return (0);
}

int	verify_syntax(char **input, int state,
		t_token *token, int error_mask)
{
	if (error_mask & OPEN_PARENTHESIS && **input == '(')
		return (print_error(SYNTAX_PREFIX, NULL, "`('"));
	else if (error_mask & CLOSE_PARENTHESIS && **input == ')')
	{
		if (is_redirection(state))
		{
			if (!(token->word))
				return (print_error(SYNTAX_PREFIX,
						NULL, "`)'"));
		}
		else
			return (print_error(SYNTAX_PREFIX, NULL, "`)'"));
	}
	else
		return (verify_syntax_2(input, state, token, error_mask));
	return (0);
}
