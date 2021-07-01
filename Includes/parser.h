#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

int			exe_create_env(t_exe_args *exe_args);
int			exe_pwd(t_exe_args *exe_args);
int			exe_echo(t_exe_args *exe_args);
int			exe_exit(t_exe_args *exe_args);
int			invalid_input(t_exe_args *exe_args);

/*
** separator.c
*/
char		get_separator(char *arg);
void		cut_separator(char **arg, char separator);

/*
** concatenate.c
*/
void		concat_args(t_exe_args exe_args, char **first, char *second,
				t_exe_info *exe_info);
int			is_concatenate(char **args, int i, t_exe_info *exe_info);
void		to_concatenate(char **args, int i, t_store *store,
							t_exe_info *exe_info);

/*
** parser_utils.c
*/
void		set_default_new_lst(t_list **lst);
char		*get_str_to_compare(char **args, t_exe_args exe_args, int *i,
						t_exe_info *exe_info);
void		init_arg(t_exe_info **tmp_lst, char *str);
int			init_data_dollar_count(int **info_arr, t_list **head);
int			validate_flag_n(char *str, t_exe_info *exe_info);

/*
** split_utils.c
*/
int			is_word_to_cont(char *str, char sep, int i);
int			init_data_word_count(char *sep, int **info_arr, t_list **head);
void		init_escape_symbol(char *sep, int **info_arr, t_list **head,
								int *i);

/*
** dollar_utils.c
*/
char		*get_tail(char *arr_str, int *i);
char		*get_str_dollar(t_exe_args exe_args, char *arr_str, int *i);

/*
** split.c
*/
char		**split(char const *s);
char		**init_arr_2d(char *str, t_list *copy_dw);

/*
** dollar.c
*/
char		*dollar_sign(char *arg, t_exe_args exe_args, t_exe_info *exe_info);

/*
** parser.c
*/
t_list		*get_exe_info(char **args, t_store *store, char *input);
int			check_valid_operator(char *input, t_exe_args *exe_args);
int			compare_with_redirect(char c);
int			compare_with_non_redirect(char c);
int			find_closest_redirect_index(char *input, int end);
int			find_index_prev_semicolon(char *input, int current_index);
void		create_and_write_error(char *token, t_exe_args *exec_args);
int			check_spaces_between(char *input, int end, int start);
char		*get_double_token(char *input, int end, int start);
int			make_currect_error(int i, int j, char *input, t_exe_args *exe_args);
int			check_input_without_redirect(char *input, t_exe_args *exe_args);
int			check_input_with_redirect(char *input, t_exe_args *exe_args);

#endif
