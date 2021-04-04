/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 19:25:52 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 20:00:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_args(char ***exec_args, t_exe_info *exe_info_next)
{
	char	**args_copy;
	char	**next_arg_arr;
	int		i;

	i = 1;
	next_arg_arr = ft_split(exe_info_next->args, ' ');
	while (next_arg_arr[i])
	{
		args_copy = copy_2d_arr(*exec_args);
		free_2d_arr(*exec_args);
		*exec_args = add_param_to_2d_arr(args_copy, next_arg_arr[i]);
		free_2d_arr(args_copy);
		i++;
	}
	free_2d_arr(next_arg_arr);
}
