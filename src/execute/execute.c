#include "minishell.h"

char	**get_args(t_exe_info *exe_info, t_support_parsing_data support)
{
	char	**args;
	char	*copy_arg;

	copy_arg = ft_strdup(exe_info->args);
	if (exe_info->exe_function == support.exe_func_arr[1])
	{
		if (ft_strlen(copy_arg) == 1)
		{
			args = (char **)malloc(sizeof(char *) + 2);
			args[0] = ft_strdup(copy_arg);
			args[1] = NULL;
		}
		else
			args = ft_split(copy_arg, '\0');
	}
	else
		args = copy_2d_arr(exe_info->double_arr_args);
	free(copy_arg);
	return (args);
}

void	run_oper_exec_function(t_exe_args *exec_args,
	t_exe_info *exe_info, t_list **info)
{
	int i;

	if (!check_is_all_command(*info, exec_args))
		i = ft_lstsize(*info) - 1;
	else
		i = exe_info->oper_exe_func(exec_args, *info);
	while (i--)
		*info = (*info)->next;
}

int		choose_command_and_run(t_exe_info *exe_info, t_store *store,
	t_list **info)
{
	char		*bin_exe_path;

	if (exe_info->oper_exe_func &&
		exe_info->oper_exe_func != exe_oper_semicolon)
		run_oper_exec_function(&store->exe_args, exe_info, info);
	else if (exe_info->exe_function)
		exe_info->exe_function(&store->exe_args);
	else if ((bin_exe_path = search(&store->exe_args,
		get_env_param("PATH", store->exe_args.env))))
	{
		launch_process(store->exe_args, bin_exe_path);
		free(bin_exe_path);
	}
	else if (store->exe_args.args[0] && !store->exe_args.args[0][0])
		invalid_input(&store->exe_args);
	else if (!ft_strlen(exe_info->args))
		return (1);
	else if (get_env_param("PATH", store->exe_args.env))
		invalid_input(&store->exe_args);
	return (0);
}

int		execute(t_store *store)
{
	t_list		*info;
	t_exe_info	*exe_info;

	info = store->exe_info;
	while (info)
	{
		exe_info = info->content;
		store->exe_args.args = get_args(exe_info, store->support);
		store->exe_args.is_flag_n = exe_info->is_flag_n;
		if (choose_command_and_run(exe_info, store, &info))
		{
			free_2d_arr(store->exe_args.args);
			return (1);
		}
		free_2d_arr(store->exe_args.args);
		info = info->next;
	}
	return (1);
}
