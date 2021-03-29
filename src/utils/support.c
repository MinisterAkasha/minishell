/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/03/29 15:34:53 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error_message(char *message_title, char *message_body, char *message_error)
{
	char	*error;

	error = ft_strjoin(": ", message_error);
	ft_putstr_fd(message_title, 1);
	ft_putstr_fd(message_body, 1);
	ft_putendl_fd(error, 1);
	free(error);
}





