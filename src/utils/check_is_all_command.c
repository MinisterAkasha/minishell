/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_all_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:43:45 by akasha            #+#    #+#             */
/*   Updated: 2021/04/15 14:44:08 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_empty_fd(t_list *info, t_exe_args *exec_args)
{
	t_exe_info	*exe_info;

	exe_info = info->next->content;
	if (exe_info->args[0] == 0)
	{
		add_variable(&exec_args->variables, create_var("?", "258", 0, 0));
		write_error("minihsell", "",
			"syntax error near unexpected token `newline'");
		return (0);
	}
	return (1);
}

int		check_is_all_command(t_list *info, t_exe_args *exec_args)
{
	t_list		*tmp;
	t_exe_info	*exe_info;

	tmp = info;
	while (tmp)
	{
		exe_info = tmp->content;
		if (exe_info->oper_exe_func == exe_oper_pipe && !tmp->next)
			return (0);
		else if (!tmp->next && check_is_redirect_funtion(exe_info))
		{
			add_variable(&exec_args->variables, create_var("?", "258", 0, 0));
			write_error("minihsell", "",
				"syntax error near unexpected token `newline'");
			return (0);
		}
		else if (tmp->next && check_is_redirect_funtion(exe_info))
		{
			if (!check_empty_fd(tmp, exec_args))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
