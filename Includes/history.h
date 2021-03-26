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

int		gnl(char **line);
int		find_nl(char **str_stat, char **line, char *tmp);
int		get_next_hist_str();
int		get_previos_hist_str();
int		delete_char(char **str);

#endif
