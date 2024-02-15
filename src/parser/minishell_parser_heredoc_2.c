/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_heredoc_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:54:28 by llapage           #+#    #+#             */
/*   Updated: 2023/09/28 14:28:12 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

int	heredoc_handler_3(int fd, char *root_dir)
{
	if (close(fd) == -1)
		return (-1);
	if (g_exit_code == 1)
	{
		set_exit_code(1, NULL, root_dir);
		sig_handler_init();
		return (-2);
	}
	sig_handler_init();
	return (0);
}
