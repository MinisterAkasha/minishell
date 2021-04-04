/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:19:30 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 19:59:31 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(char **env)
{
	char	*lvl;
	char	**env_copy;
	int		cur_shlvl;

	if (get_env_param("SHLVL", env))
	{
		cur_shlvl = ft_atoi(ft_strchr(get_env_param("SHLVL", env), '=') + 1);
		lvl = ft_itoa(cur_shlvl + 1);
		change_env_value(lvl, "SHLVL", &env);
		free(lvl);
	}
	else
	{
		env_copy = copy_2d_arr(env);
		free_2d_arr(env);
		env = add_param_to_2d_arr(env_copy, "SHLVL=1");
		free_2d_arr(env_copy);
	}
}
