/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:43:06 by tilda             #+#    #+#             */
/*   Updated: 2021/03/19 15:43:07 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** protect_malloc.c
*/
void	error_malloc();
void	*protect_malloc(void *value);
char	**protect_ft_split(char **value);

#endif