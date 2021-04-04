/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 19:50:03 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 19:55:09 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir_path(char *pwd, char *arg)
{
	char	*dir_path;
	char	*arg_path;
	int		len;

	if (ft_strrchr(arg, '/'))
		len = ft_strlen(arg) - ft_strlen(ft_strrchr(arg, '/'));
	else
		len = ft_strlen(arg);
	arg_path = ft_substr(arg, 0, len);
	dir_path = ft_strjoin(pwd, arg_path);
	free(arg_path);
	return (dir_path);
}

char	*get_relative_path(char *arg)
{
	char	*current_path;
	char	*command;
	char	pwd[2048];
	char	*dir_path;
	char	*pwd_with_slash;

	getcwd(pwd, 2048);
	current_path = NULL;
	command = get_command_from_path(arg);
	pwd_with_slash = ft_strjoin(pwd, "/");
	dir_path = get_dir_path(pwd_with_slash, arg);
	if (check_dir(dir_path, command))
		current_path = ft_strjoin(pwd_with_slash, arg);
	free(command);
	free(dir_path);
	free(pwd_with_slash);
	return (current_path);
}
