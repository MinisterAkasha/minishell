/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/04/10 18:23:30 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *message_title, char *message_body,
					char *message_error)
{
	char	*error;

	if (message_error[0] != '\'')
		error = ft_strjoin(": ", message_error);
	else
		error = ft_strdup(message_error);
	ft_putstr_fd(message_title, 2);
	ft_putstr_fd(message_body, 2);
	ft_putendl_fd(error, 2);
	free(error);
}

void	reset_fd(t_exe_args *exec_args)
{
	exec_args->fd[0] = -1;
	exec_args->fd[2] = -1;
	exec_args->fd[4] = 0;
}