/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:23:49 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:56:54 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int execute(t_store *store, char **args);
int exe_env(t_exe_args *exe_args);
int	exe_cd(t_exe_args *exe_args);

#endif
