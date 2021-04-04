/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:55:49 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 21:12:18 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exe_pwd(t_exe_args *exe_args)
{
	char path[2048];

	//TODO обработать ошибки при необходимости
	ft_putendl_fd(getcwd(path, 2048), 1);
	add_variable_to_list(&exe_args->variables, create_variable("?", "0", 0, 0));
	return (1);
}