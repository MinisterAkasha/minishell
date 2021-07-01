#include "minishell.h"

char	*overflow_shlvl(int cur_lvl)
{
	char *lvl;

	lvl = ft_itoa(cur_lvl + 1);
	write(2, "minishell: warning: shell level ", 32);
	write(2, lvl, ft_strlen(lvl));
	write(2, " too high, resetting to 1\n", 27);
	free(lvl);
	lvl = ft_strdup("1");
	return (lvl);
}

void	empty_shlvl(t_exe_args *exe_args)
{
	char	**env_copy;

	env_copy = copy_2d_arr(exe_args->env_init);
	free_2d_arr(exe_args->env_init);
	free_2d_arr(exe_args->env);
	exe_args->env_init = add_param_to_2d_arr(env_copy, "SHLVL=1");
	exe_args->env = add_param_to_2d_arr(env_copy, "SHLVL=1");
	free_2d_arr(env_copy);
}

void	shlvl(t_exe_args *exe_args)
{
	char	*lvl;
	int		cur_lvl;

	if (get_env_param("SHLVL", exe_args->env_init))
	{
		cur_lvl = ft_atoi(ft_strchr(get_env_param("SHLVL", exe_args->env_init),
			'=') + 1);
		if (cur_lvl == 999)
			lvl = ft_strdup("");
		else if (cur_lvl >= 1000)
			lvl = overflow_shlvl(cur_lvl);
		else
			lvl = ft_itoa(cur_lvl + 1);
		change_env_value(lvl, "SHLVL", &exe_args->env_init);
		change_env_value(lvl, "SHLVL", &exe_args->env);
		free(lvl);
	}
	else
		empty_shlvl(exe_args);
}
