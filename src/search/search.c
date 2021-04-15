/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:12:44 by akasha            #+#    #+#             */
/*   Updated: 2021/04/14 19:14:47 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_dir(char *path, char *arg)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buff;

	dir = opendir(path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	lstat(arg, &buff);
	while (entry != NULL)
	{
		while (!ft_strcmp(entry->d_name, ".")
			|| !ft_strcmp(entry->d_name, ".."))
			entry = readdir(dir);
		if (!(ft_strcmp(arg, entry->d_name))
			&& ((buff.st_mode & S_IEXEC || !buff.st_mode)
			&& !(buff.st_mode & S_IFDIR)))
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
	if (!get_arr_length(splited_path))
		command = ft_strdup("");
	else
		command = ft_strdup(splited_path[get_arr_length(splited_path) - 1]);
	free_2d_arr(splited_path);
	return (command);
}

char	*get_current_path(char *path, char *command)
{
	char *with_slash;
	char *current_path;

	with_slash = ft_strjoin(path, "/");
	current_path = ft_strjoin(with_slash, command);
	free(with_slash);
	return (current_path);
}

char	*get_bin_path_command(char *arg, const char *path)
{
	char	**bin_paths;
	char	*current_path;
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
			if (check_currect_path(arg, bin_paths[i]))
				current_path = get_current_path(bin_paths[i], command);
			break ;
		}
		i++;
	}
	free(command);
	free_2d_arr(bin_paths);
	return (current_path);
}

char	*search(t_exe_args *exe_args, const char *path)
{
	char	*current_path;
	char	*command;

	if (!exe_args->args[0])
		return (NULL);
	if (!exe_args->args[0][0])
		return (NULL);
	if (!path)
	{
		command = get_command_from_path(exe_args->args[0]);
		add_variable(&exe_args->variables, create_var("?", "127", 0, 0));
		write_error("minishell: ", command, "No such file or directory");
		free(command);
		return (NULL);
	}
	current_path = get_bin_path_command(exe_args->args[0], path);
	if (!current_path)
		current_path = get_relative_path(exe_args->args[0]);
	return (current_path);
}
