/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:18:42 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 16:25:55 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_error_head(int (*exe_function)(t_exe_args *))
{
	if (exe_function == exe_export)
		return ("minishell: export: '");
	return ("minishell: unset: '");
}

void	check_identifier(t_list *info, int pipe_num)
{
	t_list		*tmp;
	t_exe_info	*exe;
	int			i;
	char		**vars;
	char		*error;

	tmp = info;
	while (tmp && pipe_num)
	{
		exe = tmp->content;
		if (exe->exe_function == exe_export || exe->exe_function == exe_unset)
		{
			vars = ft_split(exe->args, ' ');
			i = -1;
			while (vars[++i])
			{
				error = get_error_head(exe->exe_function);
				if (!(validate_var_name(vars[i])) && tmp->next)
					write_error(error, vars[i], "': not a valid identifier");
			}
			free_2d_arr(vars);
		}
		pipe_num--;
		tmp = tmp->next;
	}
}
