#include "minishell.h"

char	*get_dir_path(char *arg)
{
	char	*dir_path;
	int		len;

	if (ft_strrchr(arg, '/'))
		len = ft_strlen(arg) - ft_strlen(ft_strrchr(arg, '/') + 1);
	else
		len = ft_strlen(arg);
	dir_path = ft_substr(arg, 0, len);
	return (dir_path);
}

char	*get_relative_path(char *arg)
{
	char	*current_path;
	char	*command;
	char	pwd[2048];
	char	*dir_path;

	getcwd(pwd, 2048);
	current_path = NULL;
	command = get_command_from_path(arg);
	dir_path = get_dir_path(arg);
	if (check_dir(dir_path, command))
		current_path = ft_strjoin(dir_path, command);
	free(command);
	free(dir_path);
	return (current_path);
}

int		check_currect_path(char *arg, const char *bin_path)
{
	char	*path;
	int		i;

	i = 0;
	if (ft_strrchr(arg, '/'))
	{
		path = ft_substr(arg, 0, ft_strlen(arg)
			- ft_strlen(ft_strrchr(arg, '/')));
		if (!ft_strcmp(path, bin_path))
			i = 1;
		free(path);
	}
	else
		i = 1;
	return (i);
}
