/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:12:44 by akasha            #+#    #+#             */
/*   Updated: 2021/04/09 15:46:31 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_dir(char *path, char *arg)
{
	DIR				*dir;
	struct dirent	*entry;

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
	char	**splited_path;
	char	*command;

	splited_path = ft_split(path, '/');
	command = ft_strdup(splited_path[get_arr_length(splited_path) - 1]);
	free_2d_arr(splited_path);
	return (command);
}

char	*get_bin_path_command(char *arg, const char *path)
{
	char	**bin_paths;
	char	*current_path;
	char	*with_slash;
	char	*command;
	int		i;

	i = 0;
	command = get_command_from_path(arg);
	bin_paths = ft_split(ft_strchr(path, '=') + 1, ':');
	current_path = NULL;
	while (bin_paths[i])
	{
		if (check_dir(bin_paths[i], command))
		{
			with_slash = ft_strjoin(bin_paths[i], "/");
			current_path = ft_strjoin(with_slash, command);
			free(with_slash);
			break ;
		}
		i++;
	}
	free(command);
	free_2d_arr(bin_paths);
	return (current_path);
}

char	*search(char *arg, const char *path)
{
	char	*current_path;
	char	*command;

	if (!arg)
		return (NULL);
	if (!path)
	{
		command = get_command_from_path(arg);
		write_error("minishell: ", command, "No such file or directory");
		free(command);
		return (NULL);
	}
	current_path = get_bin_path_command(arg, path);
	if (!current_path)
		current_path = get_relative_path(arg);
	return (current_path);
}
