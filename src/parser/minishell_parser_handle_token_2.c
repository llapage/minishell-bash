/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_handle_token_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:19:07 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 18:01:30 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

static int	handle_input_redirection_token(t_ast **node, int *bad_file,
		t_token *token)
{
	char	*file_name;

	file_name = char_list_to_str(token->word);
	if (!(file_name))
		return (-1);
	if (access(file_name, F_OK | R_OK))
		*bad_file = 1;
	free(file_name);
	if (arg_list_add(&((*node)->infiles), token->word))
		return (-1);
	return (0);
}

static int	handle_output_redirection_token_2(t_ast **node, int *bad_file,
		t_token *token, char *file_name)
{
	int			i;
	t_arg_list	*ptr;

	i = (*node)->nbr_outfiles - 1;
	if ((!(access(file_name, F_OK)))
		&& (access(file_name, W_OK)))
		*bad_file = 1;
	free(file_name);
	if (arg_list_add(&(*node)->outfiles,
			token->word))
		return (-1);
	ptr = (*node)->outfiles;
	while (i--)
		ptr = ptr->next;
	if (token->type == OUTPUT_APPEND)
		ptr->mode = APPEND;
	else
		ptr->mode = TRUNCATE;
	return (0);
}

static int	handle_output_redirection_token(t_ast **node, int *bad_file,
		t_token *token)
{
	char	*file_name;
	char	*dir_name;

	(*node)->nbr_outfiles++;
	file_name = char_list_to_str(token->word);
	if (!(file_name))
		return (-1);
	if (ft_strchr(file_name, '/'))
	{
		dir_name = ft_strduprchr(file_name, '/');
		if (!(dir_name))
		{
			free(file_name);
			errno = ENOMEM;
			return (-1);
		}
		if (!(dir_exists(dir_name)))
			*bad_file = 1;
		free(dir_name);
	}
	return (handle_output_redirection_token_2(node, bad_file, token,
			file_name));
}

static int	handle_heredoc_token(t_ast **node, t_token *token,
		char *root_dir, char **env)
{
	char		*file_name;
	char		*heredoc_delimiter;
	t_char_list	*heredoc_cl;
	int			ret;

	heredoc_delimiter = resolve_heredoc_delimiter(&token->word);
	if (!(heredoc_delimiter))
		return (-1);
	char_list_clear(&token->word);
	token->root_dir = NULL;
	ret = heredoc_handler(heredoc_delimiter, &file_name, root_dir, env);
	if (ret)
	{
		free(heredoc_delimiter);
		free(file_name);
		return (ret);
	}
	free(heredoc_delimiter);
	heredoc_cl = str_to_char_list(file_name);
	if ((!(heredoc_cl)) || arg_list_add(&(*node)->infiles, heredoc_cl))
		return (-1);
	free(file_name);
	(*node)->heredoc_file = 1;
	return (0);
}

int	handle_token_2(t_token *token, t_ast **node, int *bad_file, char **env)
{
	int	ret;

	if (token->type == INPUT_REDIRECTION && (!(*bad_file)))
	{
		if (handle_input_redirection_token(node, bad_file, token))
			return (-1);
	}
	else if ((token->type == OUTPUT_REDIRECTION || token->type == OUTPUT_APPEND)
		&& (!(*bad_file)))
	{
		if (handle_output_redirection_token(node, bad_file, token))
			return (-1);
	}
	else if (token->type == HEREDOC && (!(*bad_file)))
	{
		ret = handle_heredoc_token(node, token, token->root_dir, env);
		if (ret)
			return (ret);
	}
	return (0);
}
