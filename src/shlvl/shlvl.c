/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:19:30 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 19:43:24 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(t_exe_args exe_args)
{
	char	*lvl;
	char	**env_copy;
	int		cur_lvl;

	if (get_env_param("SHLVL", exe_args.env_init))
	{
		cur_lvl = ft_atoi(ft_strchr(get_env_param("SHLVL",exe_args.env_init),
			'=') + 1);
		lvl = ft_itoa(cur_lvl + 1);
		change_env_value(lvl, "SHLVL", &exe_args.env_init);
		change_env_value(lvl, "SHLVL", &exe_args.env);
		free(lvl);
	}
	else
	{
		env_copy = copy_2d_arr(exe_args.env_init);
		free_2d_arr(exe_args.env_init);
		free_2d_arr(exe_args.env);
		exe_args.env_init = add_param_to_2d_arr(env_copy, "SHLVL=1");
		exe_args.env = add_param_to_2d_arr(env_copy, "SHLVL=1");
		free_2d_arr(env_copy);
	}
}
