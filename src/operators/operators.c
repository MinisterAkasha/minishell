/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:49:06 by tilda             #+#    #+#             */
/*   Updated: 2021/03/24 15:46:43 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exe_oper_semicolon(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args)
{
	return 0;
}

int		exe_oper_double_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args)
{
	printf("DOUBLE REDIRECT\n");
	return 0;
}
int		exe_oper_reverse_redirect(char **argv, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args)
{
	printf("REVERSE REDIRECT\n");
	return 0;
}