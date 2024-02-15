/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:14:30 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 19:21:03 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*trim_input(char *input)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(input, " ");
	free(input);
	if (!(trimmed_str))
	{
		errno = ENOMEM;
		print_error(PREFIX, NULL, STRERROR);
		exit(1);
	}
	return (trimmed_str);
}

char	*read_input(char *input, char *root_dir, int *buffer_overflow)
{
	if (input)
		free(input);
	input = NULL;
	input = readline("Minishell ➜ ");
	if (input
		&& ft_strlen(input) != 0
		&& history_is_new(input, root_dir))
		history_add(input, root_dir);
	if (input && ft_strlen(input) > 254)
	{
		print_error("Readline: ", NULL, "input buffer overflow");
		*buffer_overflow = 1;
		return (free(input), input = NULL, input);
	}
	if (input)
		return (trim_input(input));
	return (NULL);
}

char	*read_stdinput(void)
{
	char	*input;
	char	*tmp;

	input = get_next_line(0);
	if (!(input))
		return (NULL);
	tmp = ft_strtrim(input, "\n");
	free(input);
	if (!(tmp))
	{
		errno = ENOMEM;
		exit(print_error(PREFIX, NULL, STRERROR));
	}
	return (tmp);
}
