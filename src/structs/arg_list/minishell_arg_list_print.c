/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_arg_list_print.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:02:25 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 10:05:53 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_arg_list.h"

int	arg_list_print(t_arg_list *arg_list)
{
	t_arg_list	*args_ptr;
	int			i;

	args_ptr = arg_list;
	i = 0;
	while (args_ptr)
	{
		if (ft_pputstr_fd("arg#", 1) == -1
			|| ft_putnbr_base_fd(i, 10, 1) == -1
			|| ft_pputstr_fd("\t", 1) == -1
			|| char_list_print(args_ptr->arg) == -1
			|| ft_pputstr_fd("\n", 1) == -1) 
			return (-1);
		args_ptr = args_ptr->next;
		i++;
	}
	return (0);
}
