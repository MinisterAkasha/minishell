/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 16:29:21 by tilda             #+#    #+#             */
/*   Updated: 2021/03/15 16:29:22 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	cut_separator_init_data(int *i, char **first)
{
	*i = 0;
	*first = 0;
}

char			get_separator(char *arg)
{
	int		i;
	char	separator;

	i = 0;
	separator = 'f';
	while (arg[i] && separator == 'f')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			separator = arg[i];
		i++;
	}
	return (separator);
}

void			cut_separator(char **arg, char separator)
{
	int		i;
	int		len;
	char	*first;
	char	*second;
	int		start_index;

	cut_separator_init_data(&i, &first);
	if (separator == (*arg)[0])
		i++;
	while (1)
	{
		len = 0;
		start_index = i;
		while ((*arg)[i] != separator && (*arg)[i++])
			len++;
		if (first != 0)
			break ;
		first = ft_substr((*arg), start_index, len);
		i++;
	}
	second = ft_substr((*arg), start_index, len);
	free((*arg));
	(*arg) = ft_strjoin(first, second);
	free(first);
	free(second);
}
