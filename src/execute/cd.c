#include "minishell.h"

int		cd_home(char *home, t_exe_args **exe_args)
{
	int		res;
	char	**home_arr;

	if (!home)
	{
		write_error("minishell: ", "cd", "HOME not set");
		res = -2;
	}
	else
	{
		home_arr = ft_split(home, '=');
		res = chdir(home_arr[1]);
		free_2d_arr((*exe_args)->args);
		(*exe_args)->args = (char **)malloc(sizeof(char*) * 2);
		(*exe_args)->args[0] = ft_strdup(home_arr[1]);
		(*exe_args)->args[1] = NULL;
		free_2d_arr(home_arr);
	}
	return (res);
}

int		cd_oldpwd(char *oldpwd)
{
	int			res;
	char		**oldpwd_splited;

	oldpwd_splited = ft_split(oldpwd, '=');
	res = -1;
	if (!oldpwd)
	{
		write_error("minishell: ", "cd", "OLDPWD not set");
		res = -2;
	}
	else
	{
		res = chdir(oldpwd_splited[1]);
		if (res == -1)
		{
			write_error("minishell: cd: ", oldpwd_splited[1], strerror(errno));
			res = -2;
		}
		free_2d_arr(oldpwd_splited);
	}
	return (res);
}

void	cd_success(char old_pwd[2048], char new_pwd[2048],
	t_exe_args **exe_args)
{
	char		**env_copy;
	char		*new_param;
	t_variable	*var;

	change_env_value(new_pwd, "PWD", &(*exe_args)->env);
	change_env_value(new_pwd, "PWD", &(*exe_args)->env_init);
	if (!get_env_param("OLDPWD", (*exe_args)->env))
	{
		new_param = ft_strjoin("OLDPWD=", old_pwd);
		env_copy = copy_2d_arr((*exe_args)->env);
		free_2d_arr((*exe_args)->env);
		free_2d_arr((*exe_args)->env_init);
		(*exe_args)->env = add_param_to_2d_arr(env_copy, new_param);
		(*exe_args)->env_init = add_param_to_2d_arr(env_copy, new_param);
		free_2d_arr(env_copy);
		free(new_param);
		var = find_variable((*exe_args)->variables, "OLDPWD");
		ft_lstdelone_var(&(*exe_args)->variables, delete_var, var);
	}
	else
	{
		change_env_value(old_pwd, "OLDPWD", &(*exe_args)->env);
		change_env_value(old_pwd, "OLDPWD", &(*exe_args)->env_init);
	}
	add_variable(&(*exe_args)->variables, create_var("?", "0", 0, 0));
}

int		commom_cd(t_exe_args *exe_args)
{
	if (exe_args->args[0][0])
		return (chdir(exe_args->args[0]));
	else
		add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	return (1);
}

int		exe_cd(t_exe_args *exe_args)
{
	int		res;
	char	old_pwd[2048];
	char	new_pwd[2048];

	getcwd(old_pwd, 2048);
	if (!exe_args->args[0])
		res = cd_home(get_env_param("HOME", exe_args->env), &exe_args);
	else if (!ft_strcmp(exe_args->args[0], "-"))
		res = cd_oldpwd(get_env_param("OLDPWD", exe_args->env));
	else
		res = commom_cd(exe_args);
	if (res == -1)
	{
		add_variable(&exe_args->variables,
			create_var("?", "1", 0, 0));
		write_error("minishell: cd: ", exe_args->args[0], strerror(errno));
	}
	else if (!res)
		cd_success(old_pwd, getcwd(new_pwd, 2048), &exe_args);
	else if (res < -1)
		add_variable(&exe_args->variables, create_var("?", "1", 0, 0));
	return (1);
}
