/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:38 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:57:44 by akasha           ###   ########.fr       */
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
			tmp[i] = ft_strjoin(key_pattern, value);
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
	return "no matches found";//TODO
}

char	**create_env(char **env)
{
	char	**env_copy;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	env_copy = (char **)malloc(sizeof(char*) * i);
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_copy);
}

// char	*add_env_param(char **env, char **variable)
// {
	
// }

int exe_env(t_exe_args *exe_arg)
{
	int i;

	i = 0;
	while (exe_arg->env[i])
	{
		ft_putendl_fd(exe_arg->env[i], 1);
		i++;
	}
	return (1);
}
