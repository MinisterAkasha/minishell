/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:35 by akasha            #+#    #+#             */
/*   Updated: 2021/03/11 17:47:45 by akasha           ###   ########.fr       */
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

#include <dirent.h>

# include "structures.h"

# include "execute.h"
# include "parser.h"

# include "get_next_line.h"
# include "../src/utils/libft/includes/libft.h"


/*
** loop_shell
*/
void	wait_child_process_end(pid_t id);
int		launch_shell(t_data *data, char **args);

/*
** init.c
*/
void	init_support_parsing_arr(t_support_parsing_data *data);

/*
** support.c
*/
void	free_2d_arr(char **arr);
void	write_error_message(char *message_title, char *message_body, char *message_error);

/*
** cd.c
*/
int		exe_cd(char **args, char **env);

/*
** env.c
*/
void	change_env(char *value, char *key, char ***env);
char	**create_env(char **env);


#endif