/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:38 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 16:57:51 by akasha           ###   ########.fr       */
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
			key_pattern = protect_malloc(ft_strjoin(key, "="));
			if (value)
				tmp[i] = protect_malloc(ft_strjoin(key_pattern, value));
			else
				tmp[i] = protect_malloc(ft_strjoin(key_pattern, ""));
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
		if (!(ft_strncmp(env[i], key, ft_strlen(key)))
			&& ft_strlen(key) == ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')))
		{
			return env[i];
		}
		i++;
	}
	return (NULL);
}

int exe_env(t_exe_args *exe_args)
{
	char		**env_copy;
	
	print_2d_arr(exe_args->env);
	add_variable_to_list(&exe_args->variables, "?", "0", 0, 0);
	return (1);
}
