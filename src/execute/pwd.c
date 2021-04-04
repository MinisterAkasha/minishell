/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:55:49 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 21:41:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_pwd(t_exe_args *exe_args)
{
	char path[2048];

	if (!getcwd(path, 2048))
	{
		write_error("minishell: cd: ",
			exe_args->args[0], strerror(errno));
		add_variable(&exe_args->variables,
			create_var("?", "1", 0, 0));
	}
	else
	{
		ft_putendl_fd(getcwd(path, 2048), 1);
		add_variable(&exe_args->variables,
			create_var("?", "0", 0, 0));
	}
	return (1);
}
