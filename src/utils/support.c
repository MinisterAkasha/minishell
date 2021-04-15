/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/04/15 21:34:58 by akasha           ###   ########.fr       */
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
	exec_args->fd[1] = -1;
	exec_args->fd[2] = -1;
	exec_args->fd[3] = -1;
	exec_args->fd[4] = 0;
	close(exec_args->fd[0]);
	close(exec_args->fd[2]);
}

char	*str_to_lower(char *arg)
{
	int		len;
	char	*str_lower;
	int		i;

	i = 0;
	len = ft_strlen(arg);
	str_lower = (char *)ft_calloc(len + 1, sizeof(char));
	while (arg[i])
	{
		str_lower[i] = ft_tolower(arg[i]);
		i++;
	}
	return (str_lower);
}

char	**remove_elem_2d_arr(char **arr, char *param)
{
	char	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = (char **)ft_calloc(sizeof(char *), (get_arr_length(arr) + 1));
	while (arr[i])
	{
		if (ft_strcmp(arr[i], param))
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	new_arr[j] = NULL;
	return (new_arr);
}
