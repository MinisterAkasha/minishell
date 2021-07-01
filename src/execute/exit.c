#include "minishell.h"

int		check_alpha_in_string(char *str)
{
	int		i;
	char	*str_code;

	i = 0;
	str_code = ft_itoa(ft_atoi(str));
	if (!ft_strcmp(str_code, str))
	{
		free(str_code);
		return (1);
	}
	else
	{
		free(str_code);
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void	success_exit(t_exe_args *exe_args)
{
	t_variable	*var;

	var = find_variable(exe_args->variables, "?");
	write(1, "exit\n", 5);
	if (exe_args->args[0])
	{
		if (ft_atoi(exe_args->args[0]) < 0)
			exit((ft_atoi(exe_args->args[0]) + 256) % 256);
		else
			exit(ft_atoi(exe_args->args[0]) % 256);
	}
	else
		exit(ft_atoi(var->value));
}

int		exe_exit(t_exe_args *exe_args)
{
	int			len;

	len = get_arr_length(exe_args->args);
	if (len > 1 && check_alpha_in_string(exe_args->args[0]))
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 42);
		add_variable(&exe_args->variables, create_var("?", "1", 0, 0));
		return (1);
	}
	else if (len >= 1 && !check_alpha_in_string(exe_args->args[0]))
	{
		write_error("exit\nminishell: exit: ",
			exe_args->args[0], "numeric argument required");
		exit(255);
	}
	else
		success_exit(exe_args);
	return (1);
}
