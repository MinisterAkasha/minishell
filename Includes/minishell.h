/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:35 by akasha            #+#    #+#             */
/*   Updated: 2021/04/08 13:22:47 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

/*
** required for working with directories
*/
# include <dirent.h>
# include <sys/types.h>

# include "structures.h"

# include "execute.h"
# include "parser.h"
# include "operators.h"
# include "history.h"
# include "signals.h"
# include "search.h"

# include "../src/utils/libft/includes/libft.h"

typedef struct	s_general
{
	t_list		*variables;
}				t_general;

t_general *general;

/*
** loop_shell
*/
void	wait_child_process_end(pid_t id, t_list *var);
int		launch_shell(t_exe_args exe_args, char *bin_path);

/*
** init.c
*/
void	init_support_parsing_arr(t_support_parsing_data *data);
void	init_history_data(t_history **history);
void	init_general_signal(t_store *store);


/*
** support.c
*/
void	write_error(char *message_title, char *message_body, char *message_error);


/*
** support_arr.c
*/
void	print_2d_arr(char **arr);
char	*multiply_strjoin(char **args);
char	*triple_str_join(char *first, char *second, char *third);
int		get_int_arr_length(int **arr);
void	free_2d_arr_int(int **arr);


/*
** support_double_arr.c
*/
void	free_2d_arr(char **arr);
char	**add_param_to_2d_arr(char **arr, char *param);
int		get_arr_length(char **arr);
char	**copy_2d_arr(char **arr);
char	**remove_param_from_2d_arr(char **arr, char *param);

/*
** support_lst.c
*/
void	del_item_libft_lst(void *value);
void	exe_info_lstclear(void *value);

/*
** env.c
*/
void	change_env_value(char *value, char *key, char ***env);
char	*get_env_param(char *key, char **env);

/*
** search.c
*/
char		*search(char *arg, const char *$_path);

/*
** shlvl.c
*/
void		shlvl(t_exe_args exe_args);

/*
** variable.c
*/
t_variable *create_var(char *key, char *value, int is_exported, int is_env);
t_variable	*find_variable(t_list *variable_list, char *key);
// void		add_variable(t_list **variable_list, char *key, char *value, int is_exported, int is_env, t_variable *new_var);
void		add_variable(t_list **variable_list, t_variable *new_var);
int			validate_var_name(char *name);
int			check_var_name_chars(char *name);


#endif