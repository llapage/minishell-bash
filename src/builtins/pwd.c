/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:15:46 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/28 17:15:43 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

int	pwd(char **env)
{
	char	*pwd_value;

	pwd_value = ft_getenv("PWD", env);
	if (ft_pputstr_fd(pwd_value, 1) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
		return (-1);
	return (0);
}
