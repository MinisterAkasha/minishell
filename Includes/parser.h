/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:43:25 by akasha            #+#    #+#             */
/*   Updated: 2021/03/13 23:45:23 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_cd(char **args, char **env, t_list *variables);
int			exe_pwd(char **args, char **env, t_list *variables);
int			exe_echo(char **args, char **env, t_list *variables);
int			exe_export(char **args, char **env, t_list *variables);
int			exe_unset(char **args, char **env, t_list *variables);
int			exe_env(char **args, char **env, t_list *variables);
int			exe_exit(char **args, char **env, t_list *variables);
int			unknown_command(char **args, char **env, t_list *variables);

t_exe_info	parser(char **args, t_support_parsing_data support);

#endif