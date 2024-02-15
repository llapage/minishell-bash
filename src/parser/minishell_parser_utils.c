/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:08:57 by llapage           #+#    #+#             */
/*   Updated: 2023/10/17 16:56:29 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

int	dir_exists(char *folder)
{
	DIR	*dir;

	dir = opendir(folder);
	if (!(dir))
		return (0);
	if (closedir(dir) == -1)
		return (-1);
	return (1);
}
