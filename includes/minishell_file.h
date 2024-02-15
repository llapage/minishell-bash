/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_file.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:55:08 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 18:04:06 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FILE_H
# define MINISHELL_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../dep/libft/libft.h"
# include "minishell_errors.h"

int		file_last_line(int fd, char **last_line);
int		file_print(int fd);
int		file_copy(int dest_fd, int src_fd);

#endif
