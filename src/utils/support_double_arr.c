#include "minishell.h"

void	free_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		get_arr_length(char **arr)
{
	int len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

char	**copy_2d_arr(char **arr)
{
	char	**arr_copy;
	int		i;

	i = 0;
	arr_copy = (char **)malloc(sizeof(char*) * (get_arr_length(arr) + 1));
	if (!arr_copy)
		ft_error_malloc();
	while (arr[i])
	{
		arr_copy[i] = ft_strdup(arr[i]);
		i++;
	}
	arr_copy[i] = NULL;
	return (arr_copy);
}

char	**add_param_to_2d_arr(char **arr, char *param)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = (char **)malloc(sizeof(char *) * (get_arr_length(arr) + 2));
	if (!new_arr)
		ft_error_malloc();
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i++] = ft_strdup(param);
	new_arr[i] = NULL;
	return (new_arr);
}

char	**remove_param_from_2d_arr(char **arr, char *param)
{
	char	**new_arr;
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = (char **)ft_calloc(sizeof(char *), (get_arr_length(arr) + 1));
	if (!new_arr)
		ft_error_malloc();
	while (arr[i])
	{
		str = ft_split(arr[i], '=');
		if (ft_strcmp(str[0], param))
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
		free_2d_arr(str);
	}
	new_arr[j] = NULL;
	return (new_arr);
}
