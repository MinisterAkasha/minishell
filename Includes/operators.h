/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:52:44 by tilda             #+#    #+#             */
/*   Updated: 2021/03/29 15:19:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

#include "structures.h"

int		exe_oper_semicolon(t_exe_args *exec_args, t_list *info);
int		exe_oper_pipe(t_exe_args *exec_args, t_list *info);
int		exe_oper_redirect(t_exe_args *exec_args, t_list *info);
int		exe_oper_double_redirect(t_exe_args *exec_args, t_list *info);
int		exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info);

void	add_args(char ***exec_args, t_exe_info	*exe_info_next);

#endif