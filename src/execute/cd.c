/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 22:05:07 by akasha           ###   ########.fr       */
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

static int run_star_path_cd(char *path)
{
	DIR *dir;
	struct dirent *entry;
	int res;

	if (!(dir = opendir(path)))
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
	char *cd_path;
	char path[100];
	char *pwd;
	int res;
	
	cd_path = args[1]; // TODO добавить trim();
	if (!ft_strcmp(cd_path, "*"))
		res = run_star_path_cd(getcwd(path, 100));
	else
		res = run_basic_path_cd(cd_path);
	return (res);
}