/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 20:34:30 by tilda             #+#    #+#             */
/*   Updated: 2021/03/21 20:34:31 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

/*
** gnl.c
*/
void			gnl(char **line, t_history *history, char **env);

/*
** keys.c
*/
void			set_str_key_up(char **str_stat, t_history *history);
void			set_str_key_down(char **str_stat, t_history *history);
void			delete_char(char **str);
void			set_alpha(char **str_stat, char *buff, t_history *history);

/*
** gnl_support.c
*/
struct termios	init_term_history(t_history *history, char **env);
int				ft_putchar(int c);
void			create_new_history(t_history *history, char *line);
int				exit_gnl(t_history *history, struct termios term_default,
						int state);

/*
** signal_keys.c
*/
void			ctrl_d(char **buff, char **str_stat);
void			ctrl_c(char **buff, char **str_stat);
void			ctrl_slash(char **buff);

#endif
