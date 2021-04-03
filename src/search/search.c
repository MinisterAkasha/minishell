/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:12:44 by akasha            #+#    #+#             */
/*   Updated: 2021/03/23 18:20:59 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir(char *path, char *arg)
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

static char	*get_command_from_path(char *path)
{
	char **splited_path;
	char *command;

	splited_path = protect_ft_split(ft_split(path, '/'));
	command = protect_malloc(ft_strdup(splited_path[get_arr_length(splited_path) - 1]));
	free_2d_arr(splited_path);
	return (command);
}

static char	*get_bin_path_command(char *arg, const char *$_path)
{
	char	**bin_paths;
	char	*current_path;
	char	*with_slash;
	char	*command;
	int		i = 0;

	command = get_command_from_path(arg);
	bin_paths = protect_ft_split(ft_split(ft_strchr($_path, '=') + 1, ':'));
	current_path = NULL;
	while (bin_paths[i])
	{
		if (check_dir(bin_paths[i], command))
		{
			with_slash = protect_malloc(ft_strjoin(bin_paths[i], "/"));
			current_path = protect_malloc(ft_strjoin(with_slash, command));
			free(with_slash);
			break;
		}
		i++;
	}
	free(command);
	free_2d_arr(bin_paths);
	return (current_path);
}

static char	*get_dir_path(char *pwd, char *arg)
{
	char	*dir_path;
	char	*arg_path;
	int		len;

	if (ft_strrchr(arg, '/'))
		len = ft_strlen(arg) - ft_strlen(ft_strrchr(arg, '/'));
	else
		len = ft_strlen(arg);
	arg_path = protect_malloc(ft_substr(arg, 0, len));
	dir_path = protect_malloc(ft_strjoin(pwd, arg_path));
	free(arg_path);
	return (dir_path);
}

static char	*get_relative_path(char *arg)
{
	char	*current_path;
	char	*command;
	char	pwd[2048];
	char	*dir_path;
	char	*pwd_with_slash;

	getcwd(pwd, 2048);
	current_path = NULL;
	command = get_command_from_path(arg);
	pwd_with_slash = protect_malloc(ft_strjoin(pwd, "/"));
	dir_path = get_dir_path(pwd_with_slash, arg);
	if (check_dir(dir_path, command))
		current_path = protect_malloc(ft_strjoin(pwd_with_slash, arg));
	free(command);
	free(dir_path);
	free(pwd_with_slash);
	return (current_path);
}

char		*search(char *arg, const char *$_path)
{
	char *current_path;

	if (!arg)
		return (NULL);
	current_path = get_bin_path_command(arg, $_path);
	if (!current_path)
		current_path = get_relative_path(arg);
	return (current_path);
}