/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:43:25 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 18:53:14 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_cd(char **args);
int			exe_pwd(char **args);
int			exe_echo(char **args);
int			exe_export(char **args);
int			exe_unset(char **args);
int			exe_env(char **args);
int			exe_exit(char **args);
int			unknown_command(char **args);

t_exe_info	parser(char **args, t_parser_data support);

#endif