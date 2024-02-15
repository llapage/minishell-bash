/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 07:48:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 19:16:48 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef TESTER
#  define TESTER 0
# endif

# include <stdio.h>
# include <readline/readline.h>
# include "../dep/libft/libft.h"
# include "minishell_lexer.h"
# include "minishell_parser.h"
# include "minishell_interpreter.h"
# include "minishell_finalizer.h"
# include "minishell_executor.h"
# include "minishell_ast.h"
# include "minishell_signals.h"
# include "minishell_builtins.h"
# include "minishell_errors.h"
# include "minishell_file.h"
# include "minishell_history.h"
# include "minishell_memory.h"

void	preliminary_checks(char **root_dir);
char	*read_input(char *input, char *root_dir, int *buffer_overflow);
char	*read_stdinput(void);

#endif
