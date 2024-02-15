/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:53:32 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 18:55:14 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_lexer.h"

int	token_add(t_token **lst, t_token *new_token)
{
	if ((!(lst)) || (!(new_token)))
		return (0);
	if (!(*lst))
	{
		*lst = new_token;
		new_token->next = new_token;
		new_token->prev = new_token;
	}
	else
	{
		new_token->next = *lst;
		new_token->prev = (*lst)->prev;
		(*lst)->prev->next = new_token;
		(*lst)->prev = new_token;
	}
	return (1);
}

int	token_clear(t_token *tokens)
{
	t_token	*token_ptr;
	t_token	*next_ptr;

	if (tokens)
	{
		token_ptr = tokens->next;
		while (token_ptr != tokens)
		{
			next_ptr = token_ptr->next;
			char_list_clear(&(token_ptr->word));
			free(token_ptr);
			token_ptr = next_ptr;
		}
		char_list_clear(&(tokens->word));
		free(tokens);
	}
	return (0);
}

t_token	*token_copy(t_token *src_token)
{
	t_token	*token_copy;

	if (!src_token)
		return (NULL);
	token_copy = malloc(sizeof(t_token));
	if (!(token_copy))
	{
		errno = ENOMEM;
		return (NULL);
	}
	token_copy->type = src_token->type;
	token_copy->word = char_list_copy(src_token->word);
	if (src_token->word && (!(token_copy->word)))
		return (NULL);
	token_copy->next = token_copy->next;
	token_copy->prev = token_copy->prev;
	return (token_copy);
}

t_token	*token_create(int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!(new_token))
	{
		errno = ENOMEM;
		return (NULL);
	}
	new_token->root_dir = NULL;
	new_token->type = type;
	new_token->word = NULL;
	new_token->next = new_token;
	new_token->prev = new_token;
	return (new_token);
}
