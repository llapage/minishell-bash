/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander_wildcard_match.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:50:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 05:20:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_expander.h"

static int	wildcard(t_char_list *pattern)
{
	if (pattern
		&& pattern->is_wildcard
		&& pattern->character == '*')
		return (1);
	return (0);
}

static char	next_real_char(t_char_list *pattern)
{
	while (pattern && wildcard(pattern))
		pattern = pattern->next;
	if (pattern)
		return (pattern->character);
	return ('\0');
}

static t_char_list	*scroll_next_real_char(t_char_list **pattern)
{
	while (*pattern && wildcard(*pattern))
		*pattern = (*pattern)->next;
	if (*pattern)
		*pattern = (*pattern)->next;
	return (*pattern);
}

int	pattern_match(char *string, t_char_list *pattern,
		t_char_list *prev_pattern)
{
	if ((!(*string)) && (!(pattern)))
		return (1);
	if (!(pattern))
		pattern = prev_pattern;
	if (!(*string) && (wildcard(pattern)))
		return (pattern_match(string, pattern->next, prev_pattern));
	else if ((!(*string)) || (!(pattern)))
		return (0);
	else if (wildcard(pattern))
	{
		if (*string == next_real_char(pattern))
		{
			prev_pattern = pattern;
			return (pattern_match(string + 1,
					scroll_next_real_char(&pattern), prev_pattern));
		}
		else
			return (pattern_match(string + 1, pattern, prev_pattern));
	}
	else if (*string == pattern->character)
		return (pattern_match(string + 1, pattern->next, prev_pattern));
	else if (wildcard(prev_pattern))
		return (pattern_match(string + 1, prev_pattern, prev_pattern));
	return (0);
}
