/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:43:13 by akasha            #+#    #+#             */
/*   Updated: 2021/03/10 17:20:04 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *create_path(char *cd_path);

// static int run_basic_path_cd(char *path)
// {
// 	int res;
// 	res = chdir(path);
// 	if (res == -1)
// 		write_error_message("minishell: cd: ", path, ": No such file or directory");
// 	return (res);
// }

// static int run_star_path_cd(char *pwd, char *cd_path)
// {
// 	DIR *dir;
// 	struct dirent *entry;
// 	int res;

// 	if (!(dir = opendir(pwd)))
// 	{
// 		// perror("diropen");
// 		// exit(1);
// 		//TODO обработать ошибку opendir
// 	}
// 	entry = readdir(dir);
// 	while (entry != NULL && entry->d_name[0] == '.')
// 		entry = readdir(dir);
// 	res = chdir(entry->d_name);
// 	if (res == -1)
// 		write_error_message("minishell: cd: ", entry->d_name, ": Not a directory");
// 	closedir(dir);
// 	return (res);
// }

int exe_cd(char **args)
{
	char **path;
	char *full_path;
	char pwd_path[100];
	int res;
	int i;

	i = 0;
	full_path = create_path(args[1]);
	res = chdir(full_path);
	if (res == -1)
		write_error_message("minishell: cd: ", full_path, ": Not a directory");
	free(full_path);
	return (res);
}

char *get_next_pwd_path(char *pwd, char *path)
{
	char *pwd_with_slash;
	char *new_pwd;

	pwd_with_slash = ft_strjoin(pwd, "/");
	new_pwd = ft_strjoin(pwd_with_slash, path);

	free(pwd_with_slash);
	return (new_pwd);
}

char *get_star_path_part(char *pwd, char *path)
{
	DIR *dir;
	struct dirent *entry;
	char *new_pwd;

	new_pwd = get_next_pwd_path(pwd, path);
	if (!(dir = opendir(pwd)))
	{
		free(new_pwd);
		return (path);
	}
	entry = readdir(dir);
	while (entry != NULL && entry->d_name[0] == '.')
		entry = readdir(dir);
	free(new_pwd);
	return (entry->d_name);
}

char *create_path(char *cd_path)
{
	char *path;
	char pwd_path[100];
	char *tmp;
	char **arr;
	int i;

	arr = ft_split(cd_path, '/');
	i = 0;
	path = ft_strdup("");
	while (arr[i])
	{
		if (i)
			tmp = ft_strjoin(path, "/");
		else
			tmp = ft_strjoin(path, "");
		free(path);
		if (arr[i][0] == '*')
			path = ft_strjoin(tmp, get_star_path_part(getcwd(pwd_path, 100), path));
		else
			path = ft_strjoin(tmp, arr[i]);
		free(tmp);
		i++;
	}

	free_2d_arr(arr);
	return (path);
}