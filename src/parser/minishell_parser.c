/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:14:36 by llapage           #+#    #+#             */
/*   Updated: 2023/10/01 18:26:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

static int	parser_failure_1(t_token *token, t_ast *head, t_ast *node)
{
	(void)node;
	token_clear(token);
	free_tree2(head);
	if (node)
	{
		free(node->args);
		free(node);
	}
	print_error(PREFIX, NULL, STRERROR);
	exit(EXIT_FAILURE);
	return (0);
}

static int	parser_failure_2(int err_no, t_token *token, t_ast *head,
	t_ast *node)
{
	if (err_no == -2)
	{
		token_clear(token);
		free_tree2(head);
		free(node->args);
		free(node);
		return (-1);
	}
	if (err_no)
		parser_failure_1(token, head, node);
	return (0);
}

static void	parser_init(t_ast **head, t_ast **node, t_token *token,
		t_token **current_token)
{
	*head = NULL;
	*node = ast_create(COMMAND);
	if (!(*node))
		parser_failure_1(token, *head, NULL);
	*current_token = token;
}

static int	parser_2(t_ast *node, t_ast **head, t_token *token)
{
	if (node->args || node->outfiles || node->infiles)
		ast_push_bottom(head, node);
	else
		free(node);
	free_tokens(token);
	return (0);
}

int	parser(t_token *token, char *root_dir, t_ast **head, char **env)
{
	t_token	*current_token;
	t_token	*last_token;
	t_ast	*node;
	int		err_no;

	parser_init(head, &node, token, &current_token);
	current_token->root_dir = root_dir;
	last_token = token->prev;
	handle_token(RESET, NULL, NULL, NULL);
	err_no = handle_token(current_token, &node, head, env);
	if (err_no)
		return (parser_failure_2(err_no, token, *head, node));
	while (current_token != last_token)
	{
		current_token = current_token->next;
		current_token->root_dir = root_dir;
		err_no = handle_token(current_token, &node, head, env);
		if (err_no)
			return (parser_failure_2(err_no, token, *head, node));
	}
	return (parser_2(node, head, token));
}
