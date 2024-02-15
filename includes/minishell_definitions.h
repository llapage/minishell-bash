/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_definitions.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:29:12 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 18:16:55 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINITIONS_H
# define MINISHELL_DEFINITIONS_H

# include "errno.h"
# include "../dep/libft/libft.h"

# define NEW_SEQUENCE 1
# define COMMAND 2
# define NEW_ARGUMENT 3
# define ARGUMENT 4
# define INPUT_REDIRECTION 5
# define OUTPUT_REDIRECTION 6
# define LOGICAL_AND 7
# define PIPE 8
# define OUTPUT_APPEND 9
# define HEREDOC 10
# define LOGICAL_OR 11
# define MAIN_STATE 15
# define DOUBLE_QUOTES 16
# define SINGLE_QUOTES 32
# define QUOTES 48
# define GREATER_THAN 16
# define SMALLER_THAN 32
# define OPEN_PARENTHESIS 128
# define CLOSE_PARENTHESIS 256
# define NO_COMMAND 1024
# define COMPLETED_TOKEN 2048
# define ACCEPTING_STATE 4096
# define AMPERSAND 8192
# define WILDCARD 16384
# define VERTICAL_BAR 32768
# define NEW_SEQUENCE_SYNTAX_MASK 41217
# define NEW_ARGUMENT_SYNTAX_MASK 131
# define COMMAND_SYNTAX_MASK 130
# define ARGUMENT_SYNTAX_MASK 132
# define INPUT_REDIRECTION_SYNTAX_MASK 57733
# define OUTPUT_REDIRECTION_SYNTAX_MASK 57734
# define OUTPUT_APPEND_SYNTAX_MASK 57785
# define HEREDOC_SYNTAX_MASK 57754
# define APPEND	1
# define TRUNCATE 2
# define REDIRECTION 1

char	*ditoa(int defined);

#endif
