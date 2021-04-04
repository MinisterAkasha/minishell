/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:49:06 by tilda             #+#    #+#             */
/*   Updated: 2021/04/04 19:49:14 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_oper_semicolon(t_exe_args *exec_args, t_list *info)
{
	return (0);
}

int	exe_oper_double_redirect(t_exe_args *exec_args, t_list *info)
{
	int	i;

	i = exe_oper_redirect(exec_args, info);
	return (i);
}

int	exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info)
{
	int	i;

	i = exe_oper_redirect(exec_args, info);
	return (i);
}
