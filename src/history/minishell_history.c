/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 08:09:17 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 16:41:34 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_history.h"

static void	history_init_2(int fd)
{
	char	*next_line;
	char	*hist_entry;

	next_line = get_next_line(fd);
	while (next_line)
	{
		hist_entry = ft_strdupchr(next_line, '\n');
		free(next_line);
		if (!(hist_entry))
		{
			errno = ENOMEM;
			print_error(PREFIX, NULL, STRERROR);
			if (close(fd) == -1)
				print_error(PREFIX, NULL, STRERROR);
			exit(EXIT_FAILURE);
		}
		add_history(hist_entry);
		free(hist_entry);
		next_line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
}

void	history_init(char *root_dir)
{
	int		fd;
	char	*hist_file;

	hist_file = ft_strjoin(root_dir, "/.cache/.minishell_history");
	if (!(hist_file))
	{
		errno = ENOMEM;
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	if (access(hist_file, F_OK))
	{
		free(hist_file);
		return ;
	}
	fd = open(hist_file, O_RDONLY);
	free(hist_file);
	if (fd == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	history_init_2(fd);
}

void	history_add(char *input, char *root_dir)
{
	int		fd;
	char	*hist_file;

	add_history(input);
	hist_file = ft_strjoin(root_dir, "/.cache/.minishell_history");
	if (!(hist_file))
	{
		free(input);
		errno = ENOMEM;
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	fd = open(hist_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(hist_file);
	if (fd == -1
		|| ft_pputstr_fd(input, fd) == -1
		|| ft_pputstr_fd("\n", fd) == -1
		|| close(fd) == -1)
	{
		free(input);
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
}

static int	history_is_new_2(char *input, int fd)
{
	char	*last_line;

	last_line = NULL;
	if (file_last_line(fd, &last_line))
	{
		free(input);
		print_error(PREFIX, NULL, STRERROR);
		if (close(fd) == -1)
			print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	if (close(fd) == -1)
	{
		free(input);
		free(last_line);
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	if (!(ft_strcmp(last_line, input)))
	{
		free(last_line);
		return (0);
	}
	free(last_line);
	return (1);
}

int	history_is_new(char *input, char *root_dir)
{
	int		fd;
	char	*hist_file;

	hist_file = ft_strjoin(root_dir, "/.cache/.minishell_history");
	if (!(hist_file))
	{
		free(input);
		errno = ENOMEM;
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	if (access(hist_file, F_OK))
	{
		free(hist_file);
		return (1);
	}
	fd = open(hist_file, O_RDONLY);
	free(hist_file);
	if (fd == -1)
	{
		free(input);
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	return (history_is_new_2(input, fd));
}
