/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ditoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:31:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 18:26:01 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_definitions.h"

char	*ditoa_2(int defined)
{
	char	*str;

	str = NULL;
	if (defined == 8)
		str = ft_strdup("PIPE");
	else if (defined == 9)
		str = ft_strdup("OUTPUT_APPEND\t");
	else if (defined == 10)
		str = ft_strdup("HEREDOC\t");
	else if (defined == 11)
		str = ft_strdup("LOGICAL_OR");
	else if (defined == 128)
		str = ft_strdup("OPEN_PARENTHESIS / SUBSHELL_START");
	else if (defined == 256)
		str = ft_strdup("CLOSE_PARENTHESIS / SUBSHELL_END");
	return (str);
}

char	*ditoa(int defined)
{
	char	*str;

	if (defined == 1)
		str = ft_strdup("NEW_SEQUENCE");
	else if (defined == 2)
		str = ft_strdup("COMMAND\t\t");
	else if (defined == 3)
		str = ft_strdup("NEW_ARGUMENT");
	else if (defined == 4)
		str = ft_strdup("ARGUMENT\t");
	else if (defined == 5)
		str = ft_strdup("INPUT_REDIRECTION\t");
	else if (defined == 6)
		str = ft_strdup("OUTPUT_REDIRECTION\t");
	else if (defined == 7)
		str = ft_strdup("LOGICAL_AND");
	else
		str = ditoa_2(defined);
	if (!(str))
		errno = ENOMEM;
	return (str);
}
