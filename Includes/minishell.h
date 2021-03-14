/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:35 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:56:58 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/wait.h>

/*
** required for working with directories
*/
# include <dirent.h>
# include <sys/types.h>

# include "structures.h"

# include "execute.h"
# include "parser.h"

# include "get_next_line.h"
# include "../src/utils/libft/includes/libft.h"


/*
** loop_shell
*/
void	wait_child_process_end(pid_t id);
int		launch_shell(char **env, char **args, char *bin_path);

/*
** init.c
*/
void	init_support_parsing_arr(t_support_parsing_data *data);

/*
** support.c
*/
void	free_2d_arr(char **arr);
void	write_error_message(char *message_title, char *message_body, char *message_error);
int		get_arr_length(char **arr);

/*
** env.c
*/
void	change_env_value(char *value, char *key, char ***env);
char	**create_env(char **env);
char	*get_env_param(char *key, char **env);

/*
** search.c
*/
char		*search(char *arg, const char *$_path);

/*
** shlvl.c
*/
void		shlvl(char **env);

/*
** variable.c
*/
t_variable	*create_variable(char *key, char *value, int is_exported);
t_variable	*find_variable(t_list *variable_list, char *key);
void		add_variable_to_list(t_list **variable_list, char *key, char *value, int is_exported);


#endif