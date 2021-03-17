/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:36:24 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 14:56:08 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variable *create_variable(char *key, char *value, int is_exported)
{
	t_variable *variable;

	variable = (t_variable*)malloc(sizeof(t_variable));
	variable->key = ft_strdup(key);
	variable->value = ft_strdup(value);
	variable->is_exported = is_exported;
	return (variable);
}

void	add_variable_to_list(t_list **variable_list, char *key, char *value, int is_exported)
{
	t_variable *variable;

	variable = find_variable(*variable_list, key);
	if (variable)
	{
		free(variable->value);
		variable->value = ft_strdup(value);
	}
	else
		ft_lstadd_front(variable_list, ft_lstnew(create_variable(key, value, is_exported)));
}

t_variable	*find_variable(t_list *variable_list, char *key)
{
	t_variable *variable;
	t_list	*tmp;

	tmp = variable_list;
	while (tmp)
	{
		variable = tmp->content;
		if (!ft_strcmp(variable->key, key))
			return (variable);
		tmp = tmp->next;
	}
	return (NULL);
}
