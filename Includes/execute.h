/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:23:49 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 13:13:56 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int	execute(t_data *data, char **args, t_support_parsing_data support, t_store *store);
int exe_env(char **args, char **env, t_list *variables);
int	exe_cd(char **args, char **env, t_list *variables);
/*
** export
*/
int		exe_export(char **args, char **env, t_list *variables);
char	**sort_export(char **env, int left, int right);
void	swap_elems(char **elem_1, char **elem_2);
#endif
