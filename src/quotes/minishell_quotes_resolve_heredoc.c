/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_resolve_heredoc.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:02:27 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 04:41:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

static void	remove_quotes(t_char_list **ptr, t_char_list **word, char type)
{
	char_list_remove(word, ptr);
	while (*ptr && (*ptr)->character != type)
		*ptr = (*ptr)->next;
	if (*ptr)
		char_list_remove(word, ptr);
}

char	*resolve_heredoc_delimiter(t_char_list **word)
{
	t_char_list	*ptr;
	char		*heredoc_delimiter;

	ptr = *word;
	while (ptr)
	{
		if (ptr->character == '\"')
			remove_quotes(&ptr, word, '\"');
		else if (ptr->character == '\'')
			remove_quotes(&ptr, word, '\'');
		else
			ptr = ptr->next;
	}
	heredoc_delimiter = char_list_to_str(*word);
	return (heredoc_delimiter);
}
