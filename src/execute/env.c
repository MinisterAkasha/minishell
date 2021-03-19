/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:38 by akasha            #+#    #+#             */
/*   Updated: 2021/03/19 13:06:23 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_value(char *value, char *key, char ***env)
{
	int i;
	char **tmp;
	char *key_pattern;

	i = 0;
	tmp = *env;
	while (tmp[i])
	{
		if (!(ft_strncmp(tmp[i], key, ft_strlen(key))))
		{
			free(tmp[i]);
			key_pattern = ft_strjoin(key, "=");
			if (value)
				tmp[i] = ft_strjoin(key_pattern, value);
			else
				tmp[i] = ft_strjoin(key_pattern, "");
			free(key_pattern);
			return ;
		}
		i++;
	}
}

char	*get_env_param(char *key, char **env)
{
	int		i;
	char	*env_param;

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], key, ft_strlen(key))))
		{
			return env[i];
		}
		i++;
	}
	return (NULL);
}

int exe_env(t_exe_args *exe_arg)
{
	char		**env_copy;
	
	fill_variable_list(exe_arg);
	env_copy = copy_2d_arr(exe_arg->env_init);
	free_2d_arr(exe_arg->env);
	exe_arg->env = fill_env_with_variables(env_copy, exe_arg->variables);
		free_2d_arr(env_copy);
	print_2d_arr(exe_arg->env);
	return (1);
}
