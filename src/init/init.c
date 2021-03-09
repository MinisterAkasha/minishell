/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:00:33 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 19:02:08 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_support_parsing_arr(t_parser_data *data)
{
	data->exe_str[0] = "cd";
	data->exe_str[1] = "echo";
	data->exe_str[2] = "pwd";
	data->exe_str[3] = "export";
	data->exe_str[4] = "unset";
	data->exe_str[5] = "env";
	data->exe_str[6] = "exit";
	data->exe_func_arr[0] = &exe_cd;
	data->exe_func_arr[1] = &exe_echo;
	data->exe_func_arr[2] = &exe_pwd;
	data->exe_func_arr[3] = &exe_export;
	data->exe_func_arr[4] = &exe_unset;
	data->exe_func_arr[5] = &exe_env;
	data->exe_func_arr[6] = &exe_exit;
}