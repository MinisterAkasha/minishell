/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:04:25 by tilda             #+#    #+#             */
/*   Updated: 2021/03/19 15:04:26 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_malloc()
{
	printf("Error: Malloc can't allocate memory \n%s\n", strerror(errno));
	exit(1);
}

/*
** Example call of the function:
** char *s = protect_malloc(ft_strdup("Hello"));
*/
void	*protect_malloc(void *value)
{
	if (!value)
		error_malloc();
	return (value);
}

/*
** Works only with ft_split()
** Example call of the function:
** char **s = protect_malloc(ft_split("Hello world", ' '));
*/
char	**protect_ft_split(char **value)
{
	if (!value)
		error_malloc();
	return (value);
}