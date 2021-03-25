/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:28:04 by tilda             #+#    #+#             */
/*   Updated: 2021/03/18 20:28:06 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			del_item_libft_lst(void *value)
{
	free(value);
	value = NULL;
}

void	exe_info_lstclear(void *value)
{
	t_exe_info	*exe_info;

	exe_info = value;
	free(exe_info->args);
	free(exe_info);
	exe_info = NULL;
}
