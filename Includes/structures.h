/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/24 15:14:01 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../src/utils/libft/includes/libft.h"

typedef struct	s_exe_args
{
	char		**env;
	char		**env_init;
	char		**args;
	int			operator_flag;
	t_list		*variables;
}				t_exe_args;

typedef struct	s_exe_info
{
	int					(*exe_function)(t_exe_args *);
	int					(*operator_exe_function)(char **args, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
	char				*args;
}				t_exe_info;

typedef struct	s_support_parsing_data
{
	char		*exe_str_arr[7];
	int			(*exe_func_arr[8])(t_exe_args *);
	int			(*operators_exe_func_arr[5])(char **args, char *next_arg, int (*exe_function)(t_exe_args *), t_exe_args fun_args);
	char		*operators_arr[5];
}				t_support_parsing_data;

typedef struct	s_variable
{
	char	*key;
	char	*value;
	int		is_exported;
	int		is_env;
}				t_variable;

typedef struct	s_store
{
	t_support_parsing_data	support;
	t_exe_args				exe_args;
	t_list					*exe_info;
}				t_store;

#endif
