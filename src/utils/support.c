/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/03/12 17:34:38 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	write_error_message(char *message_title, char *message_body, char *message_error)
{
	ft_putstr_fd(message_title, 1);
	ft_putstr_fd(message_body, 1);
	ft_putendl_fd(message_error, 1);
}

int		get_arr_length(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
