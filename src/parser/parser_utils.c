/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:30:17 by tilda             #+#    #+#             */
/*   Updated: 2021/03/16 15:30:19 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exe_create_env(t_exe_info **tmp_lst, t_support_parsing_data support, int *decrement, char *str)
{
	char	**splited_str;
	int		result;
	int		i;

	result = 1;
	i = 0;
	splited_str = ft_split(str, '=');
	if (get_arr_length(splited_str) < 2)
		result = 0;
	while (splited_str[0][i])
	{
		if (!ft_isalnum(splited_str[0][i]))
			result = 0;
		i++;
	}
	if (result == 1)
	{
		free((*tmp_lst)->arg);
		(*tmp_lst)->arg = ft_strdup(str);
		(*tmp_lst)->exe_function = support.exe_func_arr[7];
		*decrement -= 1;
	}
	free_2d_arr(splited_str);
}
