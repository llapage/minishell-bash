/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:50:15 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 18:09:53 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

int	eof_exit(char *root_dir, int interactive_mode)
{
	int	exit_status;

	if (interactive_mode && ft_pputstr_fd("exit\n", 1) == -1)
		return (EXIT_FAILURE);
	check_exit_code(NULL, root_dir, &exit_status);
	clear_cache(root_dir);
	return (exit_status);
}

static int	exit_argument_2(int argc, char **argv, char *exit_code,
		char *root_dir)
{
	if (argc == 2)
	{
		exit_code = ft_strjoin("!", argv[1]);
		if (!(exit_code))
			return (error_enomem(-1, NULL, NULL));
		if (write_exit_code(exit_code, root_dir))
			return (-1);
		free(exit_code);
		return (1);
	}
	return (0);
}

int	exit_argument(int argc, char **argv, char *exit_code, char *root_dir)
{
	char	*tmp;

	tmp = ft_strtrim(argv[1], " \t\n\r\f\v");
	if (!(tmp))
		return (error_enomem(-1, NULL, NULL));
	free(argv[1]);
	argv[1] = ft_strdup(tmp);
	free(tmp);
	if (!(argv[1]))
		return (error_enomem(-1, NULL, NULL));
	if (!(ft_isllong(argv[1])))
	{
		tmp = ft_strjoin("exit: ", argv[1]);
		if (!(tmp))
			return (error_enomem(-1, NULL, NULL));
		if (print_error(PREFIX, tmp, "numeric argument required") == -1)
			return (-1);
		if (write_exit_code("!255", root_dir))
			return (-1);
		return (1);
	}
	return (exit_argument_2(argc, argv, exit_code, root_dir));
}

int	exit_builtin(t_ast *node, int argc, char **argv, char *root_dir)
{
	char	*exit_code;
	int		ret;

	if (node->output_fd != STDOUT_FILENO || node->input_fd != STDIN_FILENO)
		return (0);
	exit_code = NULL;
	if (ft_pputstr_fd("exit\n", 1))
	{
		print_error(PREFIX, "exit", STRERROR);
		return (SYSTEM_FAILURE);
	}
	if (argv[1])
	{
		ret = exit_argument(argc, argv, exit_code, root_dir);
		if (ret == 1)
			return (0);
		else if (ret == -1)
			return (SYSTEM_FAILURE);
	}
	if (argc > 2)
		return (too_much_arguments(&ret, root_dir));
	else if (write_exit_code("!0", root_dir))
		return (SYSTEM_FAILURE);
	return (0);
}
