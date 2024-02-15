/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 05:04:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/27 15:59:38 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include "minishell_errors.h"
# include "minishell_memory.h"
# include "minishell_definitions.h"
# include "../dep/libft/libft.h"

void	sig_handler(int sig);
void	sig_ignore(void);
void	sig_handler_init(void);
void	sig_handler_heredoc(int sig);
void	sig_handler_init_heredoc(void);
void	sig_handler_wait_init(void);
void	sig_handler_wait(int sig);
void	sig_child_handler_init(void);

#endif
