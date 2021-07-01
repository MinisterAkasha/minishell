#include "minishell.h"

int	exe_oper_semicolon(t_exe_args *exec_args, t_list *info)
{
	if (exec_args->args || info)
		;
	return (0);
}

int	exe_oper_double_redirect(t_exe_args *exec_args, t_list *info)
{
	int	i;

	i = exe_oper_redirect(exec_args, info);
	return (i);
}

int	exe_oper_reverse_redirect(t_exe_args *exec_args, t_list *info)
{
	int	i;

	i = exe_oper_redirect(exec_args, info);
	return (i);
}
