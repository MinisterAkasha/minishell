/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:43:25 by akasha            #+#    #+#             */
/*   Updated: 2021/03/18 22:44:58 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_create_env(t_exe_args *exe_args);
int			exe_pwd(t_exe_args *exe_args);
int			exe_echo(t_exe_args *exe_args);
int			exe_exit(t_exe_args *exe_args);
int			unknown_command(t_exe_args *exe_args);

/*
** separator.c
*/
char		get_separator(char *arg);
void		cut_separator(char **arg, char separator);

/*
** concatenate.c
*/
void		concat_arg(t_exe_info **exe_info, char *arg);
void		concat_exe_arg(char **first, char *second);

/*
** parser_utils.c
*/
void		set_default_new_lst(t_exe_info **lst);
char		*get_str_to_compare(char **args, int *i, int *state_create_env);
void		init_arg(t_exe_info **tmp_lst, char *str, int *decrement);

/*
** split.c
*/
char		**split(char const *s);

/*
** parser.c
*/
int			get_exe_info(char **args, t_store *store);

#endif