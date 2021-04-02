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

char			get_separator(char *arg)
{
	int		i;
	char	sep;

	i = 0;
	sep = 'f';
	while (arg[i] && sep == 'f')
	{
		if (arg[i] == '"' || arg[i] == '\'')
			sep = arg[i];
		i++;
	}
	return (sep);
}

static	int		get_next_separators(char *arg, char sep, int *index)
{
	int		i;

	i = *index;
	while (arg[i])
	{
		if (arg[i] == sep && (arg[i] == '\'' || arg[i] == '"'))
		{
			*index = i;
			break ;
		}
		i++;
	}
	return (*index);
}

static	int		verify_sep(char *arg, char sep)
{
	int		nbr_sep;
	int		i;

	i = 0;
	nbr_sep = 0;
	while (arg[i])
	{
		if (arg[i] == sep && (arg[i] == '\'' || arg[i] == '"'))
			nbr_sep++;
		i++;
	}
	if (nbr_sep == 2)
		return (1);
	return (0);
}

static	int		get_len(char *arg, int *i, char sep)
{
	*i += 1;
	while (arg[*i])
	{
		if (sep == arg[*i] && (arg[*i] == '\'' || arg[*i] == '"'))
		{
			*i -= 1;
			break ;
		}
		*i += 1;
	}
	return (*i);
}

void			cut_separator(t_exe_args exe_args, char **arg, char sep)
{
	int		i;
	int		index;
	char	*first;
	char	*second;
	char	*tmp;

	if (!(verify_sep((*arg), sep)))
		return ;
	index = 0;
	i = get_next_separators(*arg, sep, &index);
	first = protect_malloc(ft_substr(*arg, 0, index));
	second = protect_malloc(ft_substr(*arg, index + 1,
								(get_len((*arg), &i, sep) - index)));
	tmp = protect_malloc(ft_strjoin(first, second));
	free(second);
	index++;
	i = get_next_separators(*arg, sep, &index);
	second = protect_malloc(ft_substr(*arg, index + 1,
									(get_len((*arg), &i, sep))));
	free((*arg));
	(*arg) = protect_malloc(ft_strjoin(tmp, second));
	free(second);
	free(first);
	free(tmp);
}
