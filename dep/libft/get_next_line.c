/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:11:50 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/10 12:11:54 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_store_front(char **store, char *newline_ptr)
{
	char	*temp;

	temp = ft_pstrdup(newline_ptr + 1);
	free(*store);
	*store = 0;
	if (!(temp))
		return (0);
	*store = ft_pstrdup(temp);
	free (temp);
	if (!(*store))
		return (0);
	return (1);
}

static int	get_next_line_update_store(char **store \
		, char *buffer, char *newline_ptr)
{
	if (!(newline_ptr))
	{
		if (!(buffer))
		{
			free(*store);
			*store = 0;
			return (1);
		}
		else
		{
			if (!(ft_strracat(store, buffer)))
			{
				*store = 0;
				return (0);
			}
			return (1);
		}
	}
	else
	{
		if (!(trim_store_front(store, newline_ptr)))
			return (0);
		return (1);
	}
}

static char	*get_next_line_get(char **store, char *newline_ptr)
{
	char	*next_line;
	size_t	len;

	if (!(newline_ptr))
		next_line = ft_pstrdup(*store);
	else
	{
		len = newline_ptr - *store + 1;
		next_line = malloc((len + 1) * sizeof(char));
		if (next_line)
			ft_strcncpy(next_line, *store, len);
	}
	if (!(next_line))
	{
		free(*store);
		*store = 0;
		return (0);
	}
	if (!(get_next_line_update_store(store, 0, newline_ptr)))
	{
		free(next_line);
		return (0);
	}
	return (next_line);
}

static int	bsr(char **store, int fd, \
		ssize_t *bytes_read, char **newline_ptr)
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	i;

	i = BUFFER_SIZE;
	buffer[i] = '\0';
	while (i-- > 0)
		buffer[i] = 0;
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
	{
		if (*store)
			*store[0] = '\0';
		return (0);
	}
	if (!(get_next_line_update_store(store, buffer, 0)))
		return (0);
	*newline_ptr = ft_strcchr(*store, '\n', BUFFER_SIZE);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*store[OPEN_MAX];
	ssize_t		bytes_read;
	char		*newline_ptr;

	if (fd > OPEN_MAX || fd < 0)
		return (0);
	newline_ptr = ft_strcchr(store[fd], '\n', BUFFER_SIZE);
	bytes_read = 0;
	if (!(newline_ptr))
		if (!(bsr(&store[fd], fd, &bytes_read, &newline_ptr)))
			return (0);
	if ((!(bytes_read)) && (!(*store[fd])))
	{
		free(store[fd]);
		store[fd] = 0;
		return (0);
	}
	while (1)
	{
		if (newline_ptr || (!(bytes_read)))
			return (get_next_line_get(&store[fd], newline_ptr));
		if (!(bsr(&store[fd], fd, &bytes_read, &newline_ptr)))
			return (0);
	}
}
