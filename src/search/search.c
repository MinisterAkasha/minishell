/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:12:44 by akasha            #+#    #+#             */
/*   Updated: 2021/03/12 16:16:57 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_arr_length(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

static int check_dir(char *path, char *arg)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(ft_strcmp(arg, entry->d_name)))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (0);
}

char	*get_command_from_path(char *path)
{
	char **splited_path;
	char *comand;

	splited_path = ft_split(path, '/');
	comand = ft_strdup(splited_path[get_arr_length(splited_path) - 1]);
	free_2d_arr(splited_path);
	return (comand);
}

static char *get_bin_path_command(char *arg, const char *$_path)
{
	char	**bin_paths;
	char	*current_path;
	char	*with_slash;
	char	*comand;
	int		i = 0;

	comand = get_command_from_path(arg);
	bin_paths = ft_split(ft_strchr($_path, '=') + 1, ':');
	current_path = NULL;
	while (bin_paths[i])
	{
		with_slash = ft_strjoin(bin_paths[i], "/");
		if (check_dir(bin_paths[i], comand))
		{
			current_path = ft_strjoin(with_slash, comand);
			break;
		}
		free(with_slash);
		i++;
	}
	free(comand);
	free(with_slash);
	free_2d_arr(bin_paths);
	return (current_path);
}

char *search(char *arg, const char *$_path)
{
	char *current_path;

	current_path = get_bin_path_command(arg, $_path);
	// if (!current_path)
	// 	current_path = get_relative_path(arg);
	return (current_path);
}