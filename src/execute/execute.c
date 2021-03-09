/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:22:26 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 20:53:42 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, char **args, t_support_parsing_data support)
{
	t_exe_info	info;

	if (!args[0])
		return (1);
	info = parser(args, support);
	info.exe_function(info.args);
	if (!ft_strcmp(info.oper, ""))
		return (1);
	else
		info.operator_exe_function(info.args);
	return (launch_shell(data, args));
}
