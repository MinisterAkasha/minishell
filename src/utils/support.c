/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/04/10 19:24:35 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *message_title, char *message_body,
					char *message_error)
{
	char	*error;

	if (message_error[0] != '\'')
		error = ft_strjoin(": ", message_error);
	else
		error = ft_strdup(message_error);
	ft_putstr_fd(message_title, 2);
	ft_putstr_fd(message_body, 2);
	ft_putendl_fd(error, 2);
	free(error);
}

void	reset_fd(t_exe_args *exec_args)
{
	exec_args->fd[0] = -1;
	exec_args->fd[2] = -1;
	exec_args->fd[4] = 0;
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
		else if (!tmp->next && (exe_info->oper_exe_func == exe_oper_redirect
		|| exe_info->oper_exe_func == exe_oper_double_redirect
		|| exe_info->oper_exe_func == exe_oper_reverse_redirect))
		{
			add_variable(&exec_args->variables, create_var("?", "258", 0, 0));
			write_error("minihsell", "", "syntax error near unexpected token 'newline'");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
