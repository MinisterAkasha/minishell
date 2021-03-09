/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:40:03 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 14:40:40 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct	s_data
{
	char		**env;
	char		**argv;
	char		*procces_name;
}				t_data;

typedef struct	s_exe_info
{
	int			(*exe_function)(char **args);
	int			(*operator_exe_function)(char **args);
	char		**args;
	char		*operator;
}				t_exe_info;

#endif