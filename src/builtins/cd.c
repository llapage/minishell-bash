/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 11:01:35 by llapage           #+#    #+#             */
/*   Updated: 2023/10/01 11:55:34 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

static int	is_absolute_path(char *arg)
{
	if (arg && arg[0] == '/')
		return (1);
	return (0);
}

int	ch_dir(char *path, char *cwd_file, char *root_dir)
{
	if (path)
	{
		if (chdir(path))
			return (1);
	}
	else if (cwd_file)
	{
		path = get_cwd(cwd_file, root_dir);
		if (!(path))
			return (SYSTEM_FAILURE);
		if (chdir(path))
			return (1);
		free(path);
	}
	return (0);
}

static int	set_cwd_write_file(t_ast *node, char *new_pwd)
{
	int		fd;

	if (!ft_getenv("PWD", node->env))
		return (0);
	fd = open(node->cwd_file, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		free(new_pwd);
		print_error(PREFIX, node->argv[0], STRERROR);
		return (SYSTEM_FAILURE);
	}
	if (ft_pputstr_fd(new_pwd, fd) == -1
		|| close(fd) == -1
		|| export_var("OLDPWD", ft_getenv("PWD", node->env), &node->env,
			node->env_file)
		|| export_var("PWD", new_pwd, &node->env, node->env_file))
	{
		free(new_pwd);
		print_error(PREFIX, node->argv[0], STRERROR);
		return (SYSTEM_FAILURE);
	}
	free(new_pwd);
	return (0);
}

static int	set_cwd_chdir(t_ast *node, char *new_pwd, char *tmp)
{
	int		ret;

	ret = ch_dir(new_pwd, USE_NEW_PWD, node->root_dir);
	if (ret)
	{
		free(new_pwd);
		print_error(PREFIX, tmp, STRERROR);
		free(tmp);
		return (ret);
	}
	return (set_cwd_write_file(node, new_pwd));
}

int	set_cwd(t_ast *node)
{
	char	*new_pwd;
	char	*tmp;

	if ((!(node->argv[1])) && ((!(ft_getenv("HOME", node->env)))))
		return (print_error(PREFIX, "cd", "HOME not set"));
	if ((!(node->argv[1])) && (!(ft_strcmp("", ft_getenv("HOME", node->env)))))
		return (0);
	if (is_absolute_path(node->argv[1]))
		new_pwd = strdup(node->argv[1]);
	else
		new_pwd = to_absolute_path(node->argv[1], node);
	cd_remove_dots(&new_pwd);
	if (node->argv[1])
		tmp = ft_strjoin("cd: ", node->argv[1]);
	else
		tmp = ft_strdup("cd: ");
	if ((!(new_pwd)) || (!(tmp)))
		return (error_enomem(SYSTEM_FAILURE, node->argv[0], new_pwd));
	return (set_cwd_chdir(node, new_pwd, tmp));
}
