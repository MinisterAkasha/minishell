/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:16:37 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 15:37:41 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info)
{
	t_list		*tmp;
	t_exe_info	*current;
	t_exe_info	*exe_info;
	t_exe_info	*exe_info_next;
	int			i;
	char		**next_arg_arr;
	int			file;
	char		*error_copy;

	i = 0;
	tmp = info;
	exe_info = tmp->content;
	current = tmp->content;
	while (tmp->next)
	{
		if (current->operator_exe_function != exe_oper_reverse_redirect)
			break ;
		exe_info_next = tmp->next->content;
		add_args(&exec_args->args, exe_info_next);
		next_arg_arr = ft_split(exe_info_next->args, ' ');
		file = open(next_arg_arr[0], O_RDWR);
		if (file == -1)
			write_error_message("minishell: ", next_arg_arr[0], strerror(errno));
		close(file);
		free_2d_arr(next_arg_arr);
		// open_and_write_to_file(exe_info_next, exe_info, exec_args, current);
		tmp = tmp->next;
		current = tmp->content;
		i++;
	}
	return (i);
}