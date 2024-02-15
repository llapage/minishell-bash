/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:08:06 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 17:15:41 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_AST_H
# define MINISHELL_AST_H

# include "minishell_arg_list.h"
# include "minishell_int_list.h"
# include "minishell_definitions.h"
# include "../dep/libft/libft.h"

enum	e_type
{
	E_COMMAND = COMMAND,
	E_AND = LOGICAL_AND,
	E_OR = LOGICAL_OR,
	E_PIPE = PIPE,
	E_SUBSHELL = OPEN_PARENTHESIS,
	E_SUBSHELL_END = CLOSE_PARENTHESIS
};

typedef struct s_ast
{
	enum e_type		type;
	int				input_fd;
	int				output_fd;
	t_int_list		*pipe_list;
	int				heredoc_file;
	int				shell_id;
	char			*env_file;
	char			*cwd_file;
	char			*root_dir;
	t_arg_list		*infiles;
	t_arg_list		*outfiles;
	t_char_list		*input_file_cl;
	t_char_list		*output_file_cl;
	t_arg_list		*args;
	char			**argv;
	int				argc;
	char			*path;
	char			**env;
	int				nbr_args;
	int				nbr_outfiles;
	int				non_blocking;
	int				no_fork;
	int				pipe_end;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*next;
	struct s_ast	*prev;
	struct s_ast	*root_node;
}	t_ast;

t_ast	*ast_create(enum e_type type);
int		ast_is_command(t_ast *node);
int		ast_is_operator(t_ast *node);
int		ast_is_subshell(t_ast *node);
int		ast_is_end_subshell(t_ast *node);
t_ast	*ast_lst_last(t_ast *head);
void	ast_push(t_ast **dest_head, t_ast **src_head);
void	ast_push_bottom(t_ast **head, t_ast *node);
t_ast	*ast_pop(t_ast **head);
int		ast_print_tree(t_ast *head);
int		ast_print_node(t_ast *node);
int		ast_print_node_args(t_ast *node);
int		ast_print_node_argv(t_ast *node);
int		ast_print_node_env(t_ast *node);
int		ast_print_stacked_nodes(t_ast *head);

#endif
