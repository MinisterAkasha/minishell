#include "minishell.h"

int			exe_pwd(t_exe_args *exe_args)
{
	char	path[2048];
	char	**pwd;

	if (!getcwd(path, 2048))
	{
		pwd = ft_split(get_env_param("PWD", exe_args->env), '=');
		printf("%s\n", pwd[1]);
		free_2d_arr(pwd);
	}
	else
	{
		ft_putendl_fd(getcwd(path, 2048), 1);
		add_variable(&exe_args->variables,
			create_var("?", "0", 0, 0));
	}
	return (1);
}
