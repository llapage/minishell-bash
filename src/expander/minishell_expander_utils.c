/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:16:00 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 14:07:15 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_expander.h"

int	free_and_return(char *file_name)
{
	free(file_name);
	return (-1);
}

int	expand_exit_code(t_char_list **char_list, char *root_dir)
{
	char	*exit_code;
	char	*file_name;
	int		fd;

	file_name = ft_strjoin(root_dir, "/.cache/.minishell_exit_code");
	if (!(file_name))
		return (error_enomem(-1, NULL, NULL));
	fd = open(file_name, O_RDONLY);
	if ((!(access(file_name, F_OK))) && fd == -1)
		return (free_and_return(file_name));
	free(file_name);
	exit_code = get_next_line(fd);
	if ((!(access(file_name, F_OK))) && close(fd) == -1)
		return (-1);
	if (g_exit_code)
		char_list_insert_str(char_list, NULL, "1");
	else if (exit_code)
		char_list_insert_str(char_list, NULL, exit_code);
	else
		char_list_insert_str(char_list, NULL, "0");
	if (fd > 0)
		free(exit_code);
	return (0);
}

int	char_list_env_expand(t_char_list **char_list, t_char_list *env_var_start,
		size_t env_var_len, char **env)
{
	char		*env_value;
	t_char_list	*insert_ptr;
	int			ret;

	ret = char_list_to_env_value(env_var_start, env_var_len, &env_value, env);
	insert_ptr = char_list_remove_range(char_list, env_var_start, env_var_len);
	if (ret)
		return (ret);
	if (char_list_insert_str(char_list, insert_ptr, env_value))
		return (SYSTEM_FAILURE);
	return (0);
}

int	char_list_to_env_value(t_char_list *env_var_start, size_t env_var_len,
		char **env_value, char **env)
{
	t_char_list	*char_ptr;
	char		*env_key;
	size_t		index;

	env_key = malloc((env_var_len + 1) * sizeof(char));
	if (!(env_key))
		return (SYSTEM_FAILURE);
	env_key[env_var_len] = '\0';
	index = 0;
	char_ptr = env_var_start;
	while (index < env_var_len)
	{
		env_key[index++] = char_ptr->character;
		char_ptr = char_ptr->next;
	}
	*env_value = ft_getenv(env_key, env);
	free(env_key);
	if (!(*env_value))
		return (1);
	return (0);
}
