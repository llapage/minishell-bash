/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:45:27 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 23:38:51 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

static int	ret_heredoc_number_ascii(char *tmp, int tmp_free)
{
	errno = ENOMEM;
	if (tmp_free)
		free(tmp);
	return (-1);
}

static int	heredoc_handler_malloc_fail(char *string_to_free)
{
	free(string_to_free);
	errno = ENOMEM;
	return (-1);
}

static int	get_new_heredoc_file(int *heredoc_number, char **heredoc_file,
		char *tmp)
{
	char	*heredoc_number_ascii;

	(*heredoc_number)++;
	heredoc_number_ascii = ft_itoa(*heredoc_number);
	free(*heredoc_file);
	if (!(heredoc_number_ascii))
		return (ret_heredoc_number_ascii(tmp, 1));
	*heredoc_file = ft_strjoin(tmp, heredoc_number_ascii);
	free(heredoc_number_ascii);
	if (!(*heredoc_file))
		return (heredoc_handler_malloc_fail(tmp));
	return (0);
}

int	heredoc_handler_2(char *delimiter, char **heredoc_file, char **env,
		char *root_dir)
{
	char	*input;
	int		fd;

	(void)env;
	fd = open(*heredoc_file, O_WRONLY | O_CREAT | O_TRUNC,
			0666);
	if (fd < 0)
		return (-1);
	sig_handler_init_heredoc();
	input = readline("> ");
	while (input && ft_strcmp(input, delimiter))
	{
		if (heredoc_expand_input(&input, env)
			|| ft_pputstr_fd(input, fd) == -1 || ft_pputstr_fd("\n", fd) == -1)
		{
			if (input)
				free(input);
			close(fd);
			return (-1);
		}
		free(input);
		input = readline("> ");
	}
	free(input);
	return (heredoc_handler_3(fd, root_dir));
}

int	heredoc_handler(char *delimiter, char **heredoc_file, char *root_dir,
		char **env)
{
	char	*tmp;
	int		heredoc_number;
	char	*heredoc_number_ascii;

	heredoc_number = 0;
	g_exit_code = 0;
	heredoc_number_ascii = ft_itoa(heredoc_number);
	if (!(heredoc_number_ascii))
		return (ret_heredoc_number_ascii(NULL, 0));
	tmp = ft_strjoin(root_dir, "/.cache/.minishell_heredoc_");
	if (!(tmp))
		heredoc_handler_malloc_fail(heredoc_number_ascii);
	*heredoc_file = ft_strjoin(tmp, heredoc_number_ascii);
	free(heredoc_number_ascii);
	if (!(*heredoc_file))
		heredoc_handler_malloc_fail(tmp);
	while (!(access(*heredoc_file, F_OK)))
		if (get_new_heredoc_file(&heredoc_number, heredoc_file, tmp))
			return (-1);
	free(tmp);
	return (heredoc_handler_2(delimiter, heredoc_file, env, root_dir));
}
