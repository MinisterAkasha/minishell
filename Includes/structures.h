/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 14:52:48 by akasha           ###   ########.fr       */
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



#endif