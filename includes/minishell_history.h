/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_history.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 07:48:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/16 09:37:42 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HISTORY_H
# define MINISHELL_HISTORY_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include "../dep/libft/libft.h"
# include "minishell_file.h"
# include "minishell_errors.h"

void	history_init(char *root_dir);
void	history_add(char *input, char *root_dir);
int		history_is_new(char *input, char *root_dir);

#endif
