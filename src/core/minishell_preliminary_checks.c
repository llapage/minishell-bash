/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_preliminary_checks.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:00:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 17:01:14 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	verify_cache(DIR *tmp)
{
	tmp = opendir(".cache");
	if (!(tmp))
		exit(print_error(PREFIX, NULL,
				"No cache dir! Execute 'mkdir .cache' to continue.."));
	if (closedir(tmp) == -1)
		exit(print_error(PREFIX, NULL, STRERROR));
}

static void	verify_pwd(DIR *tmp, char *probe, int fd, char **root_dir)
{
	tmp = opendir(*root_dir);
	if (!(tmp))
		exit(print_error(PREFIX, NULL,
				"set PWD to a valid directory with write permissions.."));
	if (closedir(tmp) == -1)
		exit(print_error(PREFIX, NULL, STRERROR));
	probe = ft_strjoin(*root_dir, "/probe");
	if (!(probe))
	{
		errno = ENOMEM;
		exit (print_error(PREFIX, NULL, STRERROR));
	}
	fd = open(probe, O_RDWR | O_CREAT);
	if (fd == -1)
	{
		free(probe);
		exit(print_error(PREFIX, NULL,
				"set PWD to a valid directory with write permissions.."));
	}
	unlink(probe);
	free(probe);
	if (close(fd) == -1)
		exit(print_error(PREFIX, NULL, STRERROR));
}

void	preliminary_checks(char **root_dir)
{
	DIR		*tmp;
	char	*probe;
	int		fd;

	tmp = NULL;
	probe = NULL;
	fd = 0;
	*root_dir = getenv("PWD");
	verify_cache(tmp);
	verify_pwd(tmp, probe, fd, root_dir);
}
