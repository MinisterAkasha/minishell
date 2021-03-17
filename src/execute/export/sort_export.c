/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 12:54:57 by akasha            #+#    #+#             */
/*   Updated: 2021/03/17 12:53:59 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int partition(char **export, int left, int right)
{
	int i;
	int j;
	int k;

	i = left;
	j = left;
	while (j <= right)
	{
		k = 0;
		while (export[j][k] <= export[right][k])
		{
			if (export[j][k] == '=' && export[right][k] == '=')
				break;
			if (export[j][k] < export[right][k])
			{
				swap_elems(&export[i], &export[j]);
				i++;
				break;
			}
			k++;
		}
		j++;
	}
	swap_elems((&export[i]), &export[right]);
	return (i);
}

void swap_elems(char **elem_1, char **elem_2)
{
	char *swap;

	swap = *elem_1;
	*elem_1 = *elem_2;
	*elem_2 = swap;
}

char **sort_export(char **export, int left, int right)
{
	int pivot;

	if (left < right)
	{
		pivot = partition(export, left, right);
		sort_export(export, left, pivot - 1);
		sort_export(export, pivot + 1, right);
	}

	return (export);
}
