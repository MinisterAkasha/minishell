/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 17:04:21 by akasha           ###   ########.fr       */
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

typedef struct	s_parser_data
{
	char		*exe_str[7];
	int			(*exe_func_arr[7])(char **);
}				t_parser_data;



#endif