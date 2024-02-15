/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:08:16 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/26 18:21:12 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOKEN_H
# define MINISHELL_TOKEN_H

# include "minishell_char_list.h"
# include "minishell_definitions.h"

typedef struct s_token
{
	int				type;
	t_char_list		*word;
	char			*root_dir;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*token_create(int type);
int		token_add(t_token **lst, t_token *new_token);
int		token_clear(t_token *head);
t_token	*token_copy(t_token *src_token);
int		token_print(t_token *head);
int		token_print_one(t_token *head);

#endif
