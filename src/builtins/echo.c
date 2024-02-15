/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:21:53 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 05:24:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

static int	write_newline(void)
{
	if (ft_pputstr_fd("\n", 1) == -1)
		return (SYSTEM_FAILURE);
	return (0);
}

static int	n_flag(char *str)
{
	if ((!(*(str + 1))) || *str++ != '-')
		return (0);
	while (*str == 'n')
		str++;
	if (*str)
		return (0);
	return (1);
}

static int	echo_2(char **argv, int i, int newline)
{
	if (i > 1)
		newline = 0;
	if (ft_pputstr_fd(argv[i], 1) == -1)
		return (SYSTEM_FAILURE);
	if (!(argv[i]))
		return (0);
	i++;
	while (argv[i])
	{
		if (ft_pputstr_fd(" ", 1) == -1
			|| ft_pputstr_fd(argv[i], 1) == -1)
			return (SYSTEM_FAILURE);
		i++;
	}
	if (newline)
		return (write_newline());
	return (0);
}

int	echo(char **argv)
{
	int	i;
	int	newline;

	if (!argv[1])
	{
		if (ft_pputstr_fd("\n", 1) == -1)
			return (SYSTEM_FAILURE);
		return (0);
	}
	i = 1;
	newline = 1;
	while (argv[i])
	{
		if (n_flag(argv[i]))
			i++;
		else
			break ;
	}
	return (echo_2(argv, i, newline));
}
