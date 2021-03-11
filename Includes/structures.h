/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/11 12:08:17 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_exe_info
{
	int			(*exe_function)(char **args);
	int			(*operator_exe_function)(char **args);
	char		**args;
	char		*oper;
}				t_exe_info;

typedef struct	s_data
{
	char		**env;
	char		**argv;
	char		*procces_name;
}				t_data;

typedef struct	s_support_parsing_data
{
	char		*exe_str_arr[7];
	int			(*exe_func_arr[7])(char **);
	char		*operators_arr[5];
}				t_support_parsing_data;

typedef struct	s_store
{
	t_support_parsing_data	support;
	t_data					input;
	t_exe_info				exe_info;
}				t_store;

#endif