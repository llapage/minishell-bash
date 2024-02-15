/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:38:09 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 20:48:01 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_file.h"

int	file_last_line(int fd, char **last_line)
{
	char	*next_line;

	errno = 0;
	next_line = get_next_line(fd);
	if (errno == ENOMEM)
		return (error_enomem(-1, NULL, NULL));
	while (next_line)
	{
		free(*last_line);
		*last_line = ft_strdupchr(next_line, '\n');
		free(next_line);
		if (!(*last_line))
			return (error_enomem(-1, NULL, NULL));
		next_line = get_next_line(fd);
	}
	return (0);
}

int	file_print(int fd)
{
	char	*next_line;

	if (ft_pputstr_fd("FILE:\nfd: ", 1) == -1
		|| ft_putnbr_base_fd(fd, 10, 1) == -1)
		return (-1);
	next_line = get_next_line(fd);
	while (next_line)
	{
		if (ft_pputstr_fd("line: ", 1) == -1
			|| ft_pputstr_fd(next_line, 1) == -1)
			return (-1);
		free (next_line);
		next_line = get_next_line(fd);
	}
	return (0);
}

int	file_copy(int dest_fd, int src_fd)
{
	char	read_buffer[1];
	int		bytes_read;

	bytes_read = read(src_fd, &read_buffer, 1);
	while (bytes_read == 1)
	{
		write(dest_fd, read_buffer, 1);
		bytes_read = read(src_fd, &read_buffer, 1);
	}
	return (0);
}
