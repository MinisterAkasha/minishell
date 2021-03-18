/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:00:33 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:02:52 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_support_parsing_arr(t_support_parsing_data *data)
{
	data->exe_str_arr[0] = "cd";
	data->exe_str_arr[1] = "echo";
	data->exe_str_arr[2] = "pwd";
	data->exe_str_arr[3] = "export";
	data->exe_str_arr[4] = "unset";
	data->exe_str_arr[5] = "env";
	data->exe_str_arr[6] = "exit";
	data->exe_func_arr[0] = &exe_cd;
	data->exe_func_arr[1] = &exe_echo;
	data->exe_func_arr[2] = &exe_pwd;
	data->exe_func_arr[3] = &exe_export;
	data->exe_func_arr[4] = &exe_unset;
	data->exe_func_arr[5] = &exe_env;
	data->exe_func_arr[6] = &exe_exit;
	data->exe_func_arr[7] = &exe_create_env;
	data->operators_arr[0] = ";";
	data->operators_arr[1] = "|";
	data->operators_arr[2] = ">";
	data->operators_arr[3] = ">>";
	data->operators_arr[4] = "<";
	data->operators_exe_func_arr[0] = &exe_oper_semicolon;
	data->operators_exe_func_arr[1] = &exe_oper_pipe;
	data->operators_exe_func_arr[2] = &exe_oper_redirect;
	data->operators_exe_func_arr[3] = &exe_oper_double_redirect;
	data->operators_exe_func_arr[4] = &exe_oper_reverse_redirect;
}