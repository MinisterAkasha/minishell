/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/13 21:05:38 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../src/utils/libft/includes/libft.h"

typedef struct	s_exe_info
{
	int			(*exe_function)(char **args, char **env);
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
	int			(*exe_func_arr[7])(char **, char **);
	char		*operators_arr[5];
}				t_support_parsing_data;

typedef struct	s_store
{
	t_support_parsing_data	support;
	t_data					input;
	t_exe_info				exe_info;
	t_list					*variables;
}				t_store;

// typedef struct	s_variables
// {
// 	char	**variables; //! [[key, value], [key, value], [key, value], [key, value]]
// 	struct s_variables *next;
// }				t_variables;

#endif