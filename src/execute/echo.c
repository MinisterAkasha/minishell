#include "minishell.h"

char	*make_new_arg_without_n(char *str)
{
	char	*new_arg;

	new_arg = ft_strdup(str + 3);
	return (new_arg);
}

int		exe_echo(t_exe_args *exe_args)
{
	ft_putstr_fd(exe_args->args[0], 1);
	if (!exe_args->is_flag_n)
		write(1, "\n", 1);
	add_variable(&exe_args->variables, create_var("?", "0", 0, 0));
	return (1);
}
