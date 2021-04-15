/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 19:51:50 by akasha            #+#    #+#             */
/*   Updated: 2021/04/12 14:54:03 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCH_H
# define SEARCH_H

char	*get_dir_path(char *arg);
char	*get_relative_path(char *arg);
int		check_dir(char *path, char *arg);
char	*get_command_from_path(char *path);
char	*get_bin_path_command(char *arg, const char *path);
char	*search(t_exe_args *exec_args, const char *path);
int		check_currect_path(char *arg, const char *bin_path);

#endif
