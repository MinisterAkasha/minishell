/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:23:49 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 14:58:34 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int		execute(t_store *store);
int		exe_unset(t_exe_args *exe_arg);
int		exe_env(t_exe_args *exe_args);
int		exe_cd(t_exe_args *exe_args);
int		cd_home(char *home);

/*
** export
*/

int		exe_export(t_exe_args *exe_arg);
void	fill_variable_list(t_exe_args *exe_arg);
char	**fill_arr_with_variable(char **arr, t_variable *$variable);
char	**fill_export_with_variables(char **env, t_list *variables);
char	**fill_env_with_variables(char **env, t_list *variables);
char	**sort_export(char **export, int left, int right);
int		partition(char **env, int left, int right);
void	swap_elems(char **elem_1, char **elem_2);

#endif
