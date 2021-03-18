/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:20:42 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 20:04:36 by akasha           ###   ########.fr       */
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

void	write_error_message(char *message_title, char *message_body, char *message_error)
{
	ft_putstr_fd(message_title, 1);
	ft_putstr_fd(message_body, 1);
	ft_putendl_fd(message_error, 1);
}


void			del_item_libft_lst(void *value)
{
	free(value);
	value = NULL;
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
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i++] = ft_strdup(param);
	new_arr[i] = NULL;
	return (new_arr);
}
