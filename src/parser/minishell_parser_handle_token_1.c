/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_handle_token_1.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:16:29 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 20:34:13 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

static int	handle_operator_token(t_token *token, t_ast **node, t_ast **head,
		int *bad_file)
{
	if ((*node)->args || (*node)->outfiles || (*node)->infiles)
	{
		ast_push_bottom(head, *node);
		*node = ast_create(token->type);
		if (!(*node))
			return (-1);
	}
	else
		(*node)->type = token->type;
	ast_push_bottom(head, *node);
	*node = ast_create(COMMAND);
	if (!(*node))
		return (-1);
	*bad_file = 0;
	return (0);
}

int	handle_token(t_token *token, t_ast **node, t_ast **head, char **env)
{
	static int	bad_file;
	int			ret;

	if (token == RESET)
		bad_file = 0;
	else if ((token->type == PIPE || token->type == LOGICAL_AND
			|| token->type == LOGICAL_OR || token->type == OPEN_PARENTHESIS
			|| token->type == CLOSE_PARENTHESIS)
		&& handle_operator_token(token, node, head, &bad_file))
		return (-1);
	else if ((token->type == COMMAND || token->type == ARGUMENT)
		&& arg_list_add(&(*node)->args, token->word))
		return (-1);
	else if (bad_file)
		return (0);
	else
	{
		ret = handle_token_2(token, node, &bad_file, env);
		if (ret)
			return (ret);
	}
	return (0);
}
