/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:43:25 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:17:07 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_pwd(t_exe_args *exe_args);
int			exe_echo(t_exe_args *exe_args);
int			exe_export(t_exe_args *exe_args);
int			exe_unset(t_exe_args *exe_args);
int			exe_exit(t_exe_args *exe_args);
int			unknown_command(t_exe_args *exe_args);
char		get_separator(char *arg);
void		cut_separator(char **arg, char separator);

//t_exe_info	parser(char **args, t_support_parsing_data support);
int			get_exe_info(char **args, t_store *store);
char		**split(char const *s);

#endif