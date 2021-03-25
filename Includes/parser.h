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
void		cut_separator(t_exe_args exe_args, char **arg, char separator);

/*
** concatenate.c
*/
void		concat_arg(t_list **tmp_lst, t_exe_args exe_args, char *arg);
void		concat_exe_arg(t_exe_args exe_args, char **first, char *second);

/*
** parser_utils.c
*/
void		set_default_new_lst(t_list **lst);
char		*get_str_to_compare(char **args, t_exe_args exe_args, int *i);
void		init_arg(t_exe_info **tmp_lst, char *str);
int			is_word_to_cont(char *str, char sep, int i);
int			init_data_dollar_count(int **info_arr, t_list **head);

/*
** split.c
*/
char		**split(char const *s);
char		**init_arr_2d(char *str, t_list *copy_dw);

/*
** dollar.c
*/
char *dollar_sign(char *arg, t_exe_args exe_args, char sep);

/*
** parser.c
*/
t_list		*get_exe_info(char **args, t_store *store);

#endif