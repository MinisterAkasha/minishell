/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:52:43 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../src/utils/libft/includes/libft.h"

typedef struct	s_exe_args
{
	char		**env;
	char		**args;
	t_list		*variables;
}				t_exe_args;

typedef struct	s_exe_info
{
	int			(*exe_function)(t_exe_args *);
	int			(*operator_exe_function)(char **args);
	char		**args;
	char		*oper;
}				t_exe_info;

typedef struct	s_support_parsing_data
{
	char		*exe_str_arr[7];
	int			(*exe_func_arr[7])(t_exe_args *);
	char		*operators_arr[5];
}				t_support_parsing_data;

typedef struct	s_variable
{
	char	*key;
	char	*value;
	int		is_exported;
}				t_variable;

typedef struct	s_store
{
	t_support_parsing_data	support;
	t_exe_info				exe_info;
	t_exe_args				exe_args;
}				t_store;

// typedef struct	s_variables
// {
// 	char	**variables; //! [[key, value], [key, value], [key, value], [key, value]]
// 	struct s_variables *next;
// }				t_variables;

#endif