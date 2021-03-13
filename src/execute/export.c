/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:36:24 by akasha            #+#    #+#             */
/*   Updated: 2021/03/13 22:11:49 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_variable(char *key, char *value)
{
	char **variable;

	variable = (char**)malloc(sizeof(char*) * 2);
	variable[0] = ft_strdup(key);
	variable[1] = ft_strdup(value);
	return (variable);
}

void	add_variable_to_list(t_list **variable_list, char *key, char *value)
{
	ft_lstadd_front(variable_list, ft_lstnew(create_variable(key, value)));
}

char	**find_variable(t_list *variable_list, char *key)
{
	char	**variable;
	t_list	*tmp;

	tmp = variable_list;
	variable = variable_list->content;
	while (tmp)
	{
		variable = tmp->content;
		if (!ft_strcmp(variable[0], key))
			return (variable);
		tmp = tmp->next;
	}
	return (NULL);
}
