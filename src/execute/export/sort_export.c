/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:54:57 by akasha            #+#    #+#             */
/*   Updated: 2021/03/14 14:59:09 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		partition(char **env, int left, int right)
// {
// 	int		i;
// 	int		j;
// 	double	pivot;

// 	i = left;
// 	j = left;
// 	pivot = env[right][0];
// 	while (j <= right)
// 	{
// 		if (env[j][0] > pivot)
// 		{
// 			swap_elems(&env[i], &env[j]);
// 			swap_elems((&env[i]), &env[j]);
// 			i++;
// 		}
// 		j++;
// 	}
// 	swap_elems((&env[i]), &env[right]);
// 	return (i);
// }

// void	swap_elems(char **elem_1, char **elem_2)
// {
// 	char  *swap;

// 	swap = *elem_1;
// 	*elem_1 = *elem_2;
// 	*elem_2 = swap;
// }

// char	**sort_export(char **env, int left, int right)
// {
// 	int pivot;

// 	if (left < right)
// 	{
// 		pivot = partition(env, left, right);
// 		sort_export(env, left, pivot - 1);
// 		sort_export(env, pivot + 1, right);
// 	}

// 	return(env);
// }
