/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:52:44 by tilda             #+#    #+#             */
/*   Updated: 2021/03/24 14:47:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

#include "structures.h"

int		exe_oper_semicolon(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
int		exe_oper_pipe(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
int		exe_oper_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
int		exe_oper_double_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
int		exe_oper_reverse_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);

#endif