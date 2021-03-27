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

int		gnl(char **line, t_history *history);
int		ft_putchar(int c);
void get_str_key_up(t_history *history, char **str_stat);
void get_str_key_down(t_history *history, char **str_stat);
int		delete_char(char **str);

#endif
