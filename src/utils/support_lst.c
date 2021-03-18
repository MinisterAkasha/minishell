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

void	exe_info_lstclear(t_exe_info **lst)
{
	t_exe_info	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		free(cur->args);
		cur->args = NULL;
		free(cur);
	}
}
