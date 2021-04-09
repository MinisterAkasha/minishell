/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:52:44 by tilda             #+#    #+#             */
/*   Updated: 2021/04/09 15:11:15 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

# include "structures.h"

int		exe_oper_semicolon(t_exe_args *exec_args, t_list *info);
int		exe_oper_redirect(t_exe_args *exec_args, t_list *info);
int		exe_oper_double_redirect(t_exe_args *exec_args, t_list *info);
int		exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info);

void	add_args(char ***exec_args, t_exe_info	*exe_info_next);

int		exe_oper_pipe(t_exe_args *exec_args, t_list *info);
void	handle_pipe_command(int **fd, t_exe_info *exe_info,
	t_exe_args *exec_args, int i);
void	handle_start_pipe_command(int **fd, int i);
void	handle_end_pipe_command(int **fd, int i, t_exe_args *exec_args);
void	close_unused_fd(int **fd, int index[2]);
void	run_exe_function(t_exe_info	*exe_info, t_exe_args *exec_args);
int		get_pipe_number(t_list *info);
int		**create_pipe_fd(int num);
void	run_exe_function(t_exe_info	*exe_info, t_exe_args *exec_args);
void	run_command(char *bin_path, t_exe_info *exe_info,
	t_exe_args *exec_args);
void	kill_all_processes(int *pid, int index);
void	check_command(char *path, t_exe_info *exe_info, t_exe_args *exec_args);
int		check_redirect(int index, t_list *info,
	t_exe_args *exec_args);
void	check_identifier(t_list *info, t_exe_args *exec_args, int pipe_num);

void	add_args(char ***exec_args, t_exe_info	*exe_info_next);
#endif
