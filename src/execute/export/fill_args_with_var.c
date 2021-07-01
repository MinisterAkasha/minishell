#include "minishell.h"

char		**fill_export_with_variables(char **env, t_list *variables)
{
	char		**new_arr;
	char		**sup_arr;
	t_list		*tmp;
	t_variable	*var;

	tmp = variables;
	new_arr = copy_2d_arr(env);
	while (tmp)
	{
		var = tmp->content;
		if (var->is_exported)
		{
			sup_arr = copy_2d_arr(new_arr);
			free_2d_arr(new_arr);
			new_arr = fill_arr_with_variable(sup_arr, var);
			free_2d_arr(sup_arr);
		}
		tmp = tmp->next;
	}
	return (new_arr);
}

char		**fill_env_with_variables(char **env, t_list *variables)
{
	char		**new_arr;
	char		**sup_arr;
	t_list		*tmp;
	t_variable	*var;

	tmp = variables;
	new_arr = copy_2d_arr(env);
	while (tmp)
	{
		var = tmp->content;
		if (var->is_env)
		{
			sup_arr = copy_2d_arr(new_arr);
			free_2d_arr(new_arr);
			new_arr = fill_arr_with_variable(sup_arr, var);
			free_2d_arr(sup_arr);
		}
		tmp = tmp->next;
	}
	return (new_arr);
}

char		**fill_arr_with_variable(char **arr, t_variable *var)
{
	char *variable;
	char *key_pattern;
	char **arr_copy;

	key_pattern = ft_strjoin(var->key, "=");
	variable = ft_strjoin(key_pattern, var->value);
	arr_copy = add_param_to_2d_arr(arr, variable);
	free(variable);
	free(key_pattern);
	return (arr_copy);
}
