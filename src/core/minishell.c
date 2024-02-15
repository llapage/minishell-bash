/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:09:17 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 12:44:11 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	brain(char **input, char **env, char *root_dir)
{
	t_token	*tokens;
	t_ast	*nodes;
	int		ret;

	ret = lexer(*input, &tokens);
	if (ret)
	{
		free(*input);
		*input = NULL;
		if (ret == SYSTEM_FAILURE)
		{
			set_exit_code(1, NULL, root_dir);
			exit(1);
		}
		set_exit_code(ret, NULL, root_dir);
	}
	else
	{
		free(*input);
		*input = NULL;
		if (!(parser(tokens, root_dir, &nodes, env))
			&& (!(interpreter(&nodes)))
			&& (!(finalizer(nodes, root_dir))))
			executor(nodes, env, root_dir);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*root_dir;
	int		buffer_overflow;

	(void)argc;
	(void)argv;
	preliminary_checks(&root_dir);
	clear_cache(root_dir);
	sig_handler_init();
	history_init(root_dir);
	input = NULL;
	while (1)
	{
		buffer_overflow = 0;
		g_exit_code = 0;
		if (isatty(STDIN_FILENO))
			input = read_input(input, root_dir, &buffer_overflow);
		else
			input = read_stdinput();
		if ((!(input)) && (!(buffer_overflow)))
			return (eof_exit(root_dir, isatty((STDIN_FILENO))));
		if (input && input[0] != 0 && (!(buffer_overflow)))
			brain(&input, env, root_dir);
	}
	return (-1);
}
