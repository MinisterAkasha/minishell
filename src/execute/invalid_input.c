#include "minishell.h"

static void	invalid_input_path(t_exe_args *exe_arg)
{
	DIR			*dir;
	int			res;

	dir = opendir(exe_arg->args[0]);
	res = execve(exe_arg->args[0], exe_arg->args, exe_arg->env);
	if (dir)
	{
		write_error("minishell: ", exe_arg->args[0], "is a directory");
		add_variable(&exe_arg->variables, create_var("?", "126", 0, 0));
		closedir(dir);
	}
	else if (res == -1)
	{
		write_error("minishell: ", exe_arg->args[0], strerror(errno));
		if (errno == 2)
			add_variable(&exe_arg->variables, create_var("?", "127", 0, 0));
		else
			add_variable(&exe_arg->variables, create_var("?", "126", 0, 0));
	}
}

static void	unknown_command(t_exe_args *exe_arg)
{
	write_error("minishell: ", exe_arg->args[0], "command not found");
	add_variable(&exe_arg->variables, create_var("?", "127", 0, 0));
}

static void	empty_filename(t_exe_args *exe_arg)
{
	write_error("minishell: ", exe_arg->args[0],
		"filename argument required\n.: usage: . filename [arguments]");
	add_variable(&exe_arg->variables, create_var("?", "2", 0, 0));
}

int			invalid_input(t_exe_args *exe_arg)
{
	if (!ft_strcmp(exe_arg->args[0], "."))
		empty_filename(exe_arg);
	else if (ft_strchr(exe_arg->args[0], '/'))
		invalid_input_path(exe_arg);
	else
		unknown_command(exe_arg);
	return (1);
}
