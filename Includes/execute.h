/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:23:49 by akasha            #+#    #+#             */
/*   Updated: 2021/03/18 15:51:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int exe_env(t_exe_args *exe_args);
int	exe_cd(t_exe_args *exe_args);
/*
** execute
*/
int		execute(t_store *store);
char	**sort_export(char **export, int left, int right);
int		partition(char **env, int left, int right);
void	swap_elems(char **elem_1, char **elem_2);

/*
** export.c
*/
int		exe_export(t_exe_args *exe_arg);
void	fill_variable_list(t_exe_args *exe_arg);
char	**fill_arr_with_variable(char **arr, t_variable *$variable);
char	**fill_export_with_variables(char **env, t_list *variables);
char	**fill_env_with_variables(char **env, t_list *variables);

#endif
