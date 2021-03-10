/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/10 13:17:47 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int run_basic_path_cd(char *path)
{
	int res;
	res = chdir(path);
	if (res == -1)
		write_error_message("minishell: cd: ", path, ": No such file or directory");
	return (res);
}

static int run_star_path_cd(char *pwd, char *cd_path)
{
	DIR *dir;
	struct dirent *entry;
	int res;

	if (!(dir = opendir(pwd)))
	{
		// perror("diropen");
		// exit(1);
		//TODO обработать ошибку opendir
	}
	entry = readdir(dir);
	while (entry != NULL && entry->d_name[0] == '.')
		entry = readdir(dir);
	res = chdir(entry->d_name);
	if (res == -1)
		write_error_message("minishell: cd: ", entry->d_name, ": Not a directory");
	closedir(dir);
	return (res);
}

int exe_cd(char **args)
{
	char	pwd_path[100];
	char	**path;
	int		res;
	int		i;

	path = ft_split(args[1], '/');
	i = 0;
	while (path[i])
	{
		if (!path[i])
			return (1);
		else if (!ft_strcmp(path[i], "*"))
			res = run_star_path_cd(getcwd(pwd_path, 100), path[i]);
		else
			res = run_basic_path_cd(path[i]);
		i++;
	}
	free_2d_arr(path);
	return (res);
}