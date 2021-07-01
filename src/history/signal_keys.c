#include "minishell.h"

void	ctrl_d(char **buff, char **str_stat)
{
	if (!ft_strcmp(*str_stat, ""))
	{
		free(*str_stat);
		*str_stat = ft_strdup("exit\n");
		free((*buff));
		(*buff) = ft_strdup("");
	}
	else
	{
		free((*buff));
		(*buff) = ft_strdup("");
	}
}

void	ctrl_c(char **buff, char **str_stat)
{
	free(*str_stat);
	*str_stat = ft_strdup("");
	free((*buff));
	(*buff) = ft_strdup("\n");
	add_variable(&g_general->variables, create_var("?", "1", 0, 0));
}

void	ctrl_slash(char **buff)
{
	free((*buff));
	(*buff) = ft_strdup("");
}
