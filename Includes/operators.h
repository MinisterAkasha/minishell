/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:52:44 by tilda             #+#    #+#             */
/*   Updated: 2021/03/12 17:52:46 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORS_H
# define OPERATORS_H

#include "structures.h"

int		exe_oper_semicolon(char **argv);
int		exe_oper_pipe(char **argv);
int		exe_oper_redirect(char **argv);
int		exe_oper_double_redirect(char **argv);
int		exe_oper_reverse_redirect(char **argv);

#endif