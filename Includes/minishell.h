/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:35 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 15:11:34 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>

# include <sys/types.h>
# include <sys/wait.h>

# include "structures.h"

# include "get_next_line.h"
# include "../src/utils/libft/includes/libft.h"
# include "execute.h"


t_exe_info	parser(char **args);
/*
** loop_shell
*/
void wait_child_process_end(pid_t id);
int launch_shell(t_data *data, char **args);

#endif