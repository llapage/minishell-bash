/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:10:17 by llapage           #+#    #+#             */
/*   Updated: 2023/09/28 15:31:45 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_signals.h"

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (ft_pputstr_fd("\n", 1) == -1)
			kill(0, SIGTERM);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_pputstr_fd("\033[1A", 1);
		ft_pputstr_fd("\033[K", 1);
		rl_getc_function = getc;
		g_exit_code = 1;
	}
}

void	sig_handler_init_heredoc(void)
{
	rl_catch_signals = 1;
	rl_getc_function = getc;
	signal(SIGINT, &sig_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (ft_pputstr_fd("\n", 1) == -1)
			kill(0, SIGTERM);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 1;
	}
}

void	sig_handler_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
