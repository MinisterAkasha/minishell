/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:43:25 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 19:29:00 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_cd(char **args, char **env);
int			exe_pwd(char **args, char **env);
int			exe_echo(char **args, char **env);
int			exe_export(char **args, char **env);
int			exe_unset(char **args, char **env);
int			exe_env(char **args, char **env);
int			exe_exit(char **args, char **env);
int			unknown_command(char **args, char **env);

//t_exe_info	parser(char **args, t_support_parsing_data support);
void		get_exe_info(char **args, t_store *store);
char		**split(char const *s);

#endif