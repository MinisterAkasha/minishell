#include "minishell.h"

void	print_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], 1);
		i++;
	}
}

char	*multiply_strjoin(char **args)
{
	int		i;
	char	*tmp_str;
	char	*tmp_arg;
	char	*str;

	if (!args)
		return (NULL);
	i = 0;
	str = ft_strdup("");
	tmp_str = ft_strdup("");
	while (args[i])
	{
		free(str);
		tmp_arg = ft_strdup(args[i]);
		str = ft_strjoin(tmp_str, tmp_arg);
		free(tmp_str);
		free(tmp_arg);
		tmp_str = ft_strdup(str);
		i++;
	}
	if (tmp_str)
		free(tmp_str);
	return (str);
}

char	*triple_str_join(char *first, char *second, char *third)
{
	char	*result_str;
	char	*tmp_str;

	tmp_str = ft_strjoin(first, second);
	result_str = ft_strjoin(tmp_str, third);
	free(tmp_str);
	return (result_str);
}

int		get_int_arr_length(int **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	free_2d_arr_int(int **arr)
{
	int	i;
	int len;

	i = 0;
	len = get_int_arr_length(arr);
	while (i < len)
		free(arr[i++]);
	free(arr);
}
