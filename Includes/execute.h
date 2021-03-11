/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:23:49 by akasha            #+#    #+#             */
/*   Updated: 2021/03/11 16:25:48 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int execute(t_data *data, char **args, t_support_parsing_data support);
int exe_env(char **args, char **env);
int	exe_cd(char **args, char **env);

#endif
