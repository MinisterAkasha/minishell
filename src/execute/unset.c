/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:56:27 by akasha            #+#    #+#             */
/*   Updated: 2021/04/04 21:12:24 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void delete_var(void *ptr)
{
	t_variable *var;

	var = ptr;
	free(var->key);
	free(var->value);
	var->key = NULL;
	var->value = NULL;
}

void ft_lstdelone_var(t_list **lst, void (*del)(void *), t_variable *var)
{
	t_list		*cur;
	t_list		*deleted_elem;
	t_variable	*cur_var;

	if (!lst || !del || !var)
		return;
	cur = *lst;
	deleted_elem = *lst;
	cur_var = deleted_elem->content;
	while (ft_strcmp(cur_var->key, var->key))
	{
		deleted_elem = deleted_elem->next;
		cur_var = deleted_elem->content;
	}
	if (cur != deleted_elem)
	{
		while (cur->next != deleted_elem)
			cur = cur->next;
		cur->next = deleted_elem->next;
	}
	else
		*lst = deleted_elem->next;
	del(cur_var);
	free(deleted_elem);
}

void		set_unset_status_var(t_exe_args *exe_arg)
{
	int		i;

	i = 0;
	while (exe_arg->args[i])
	{
		if (!validate_var_name(exe_arg->args[i]))
		{
			add_variable_to_list(&exe_arg->variables, create_variable("?", "1", 0, 0));
			return ;
		}
		i++;
	}
	add_variable_to_list(&exe_arg->variables, create_variable("?", "0", 0, 0));
}

int exe_unset(t_exe_args *exe_arg)
{
	int			i;
	char		**env_copy;
	t_variable	*var;

	i = 0;
	while (exe_arg->args[i])
	{
		if (validate_var_name(exe_arg->args[i]))
		{
			var = find_variable(exe_arg->variables, exe_arg->args[i]);
			if (var)
				ft_lstdelone_var(&exe_arg->variables, delete_var, var);
			if (get_env_param(exe_arg->args[i], exe_arg->env_init))
			{
				env_copy = copy_2d_arr(exe_arg->env_init);
				free_2d_arr(exe_arg->env_init);
				exe_arg->env_init = remove_param_from_2d_arr(env_copy, exe_arg->args[i]);
				free_2d_arr(env_copy);
			}
		}
		else
			write_error_message("minishell: unset: '", exe_arg->args[i], "': not a valid identifier");
		i++;
	}
	set_unset_status_var(exe_arg);
	env_copy = copy_2d_arr(exe_arg->env_init);
	free_2d_arr(exe_arg->env);
	exe_arg->env = fill_env_with_variables(env_copy, exe_arg->variables);
	free_2d_arr(env_copy);
	return (1);
}