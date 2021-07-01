#include "minishell.h"

void	del_item_libft_lst(void *value)
{
	free(value);
	value = NULL;
}

void	exe_info_lstclear(void *value)
{
	t_exe_info	*exe_info;

	exe_info = value;
	free_2d_arr(exe_info->double_arr_args);
	free(exe_info->args);
	free(exe_info);
	exe_info = NULL;
}
