/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/04/15 20:04:25 by akasha           ###   ########.fr       */
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
	int			fd[5];
	int			pipe_fd[2];
	int			is_flag_n;
	t_list		*variables;
}				t_exe_args;

typedef struct	s_exe_info
{
	int					(*exe_function)(t_exe_args *);
	int					(*oper_exe_func)(t_exe_args *exec_args, t_list *info);
	char				*args;
	char				**double_arr_args;
	int					is_flag_n;
}				t_exe_info;

typedef struct	s_support_parsing_data
{
	char		*exe_str_arr[7];
	int			(*exe_func_arr[7])(t_exe_args *);
	int			(*operators_exe_func_arr[5])
		(t_exe_args *exec_args, t_list *info);
	char		*operators_arr[5];
}				t_support_parsing_data;

typedef struct	s_variable
{
	char	*key;
	char	*value;
	int		is_exported;
	int		is_env;
}				t_variable;

typedef struct	s_history
{
	char	**arr;
	char	*first_str;
	int		cur;
	int		total;
	int		is_new_str;
}				t_history;

typedef struct	s_store
{
	t_support_parsing_data	support;
	t_exe_args				exe_args;
	t_list					*exe_info;
}				t_store;

#endif
