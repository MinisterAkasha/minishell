/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/03/09 20:46:55 by akasha           ###   ########.fr       */
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
}

void	write_error_message(char *message_title, char *message_body, char *message_error)
{
	ft_putstr_fd(message_title, 1);
	ft_putstr_fd(message_body, 1);
	ft_putendl_fd(message_error, 1);
}
