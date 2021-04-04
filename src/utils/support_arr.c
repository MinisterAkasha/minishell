/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:27:58 by tilda             #+#    #+#             */
/*   Updated: 2021/04/02 15:50:30 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], 1);
		i++;
	}
}

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
		error_malloc();
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
		error_malloc();
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
	new_arr = (char **)malloc(sizeof(char *) * (get_arr_length(arr)));
	if (!new_arr)
		error_malloc();
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

char		*multiply_strjoin(char **args)
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

int		get_int_arr_length(int **arr)
{
	int len;

	len = 0;
	while(arr[len])
		len++;
	return (len);
}

void	free_2d_arr_int(int **arr)
{
	int	i;
	int len;

	i = 0;
	len = get_int_arr_length(arr);
	while(i < len)
		free(arr[i++]);
	free(arr);
}