/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 22:12:44 by akasha            #+#    #+#             */
/*   Updated: 2021/03/12 13:35:46 by akasha           ###   ########.fr       */
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
		if (!ft_strcmp(arg, entry->d_name))
		{
			closedir(dir);
			return (1);
		}
		entry = readdir(dir);
    }
    closedir(dir);
	return (0);
}

char		*search(char *arg, const char *$_path)
{
	char	**bin_paths;
	char	*current_path;
	char	*with_slash;
	int		i = 0;

	bin_paths = ft_split(ft_strchr($_path, '=') + 1, ':');
	while (bin_paths[i])
	{
		if (check_dir(bin_paths[i], arg))
		{
			with_slash = ft_strjoin(bin_paths[i], "/");
			current_path = ft_strjoin(with_slash, arg);
			free(with_slash);
			return (current_path);
		}
		i++;
	}
	free_2d_arr(bin_paths);
	return (NULL);
}