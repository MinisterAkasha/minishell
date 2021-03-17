/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:30:17 by tilda             #+#    #+#             */
/*   Updated: 2021/03/16 15:30:19 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	verify_exe_create_env(char *str, int *state_env)
{
	int		i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=' && *state_env == 0)
			*state_env = 1;
		else if (str[i] == '=' && *state_env == 2)
			*state_env = 3;
		else if (str[i] != '=' && !ft_isalnum(str[i]))
		{
			if (*state_env == 0)
				*state_env = 2;
		}
		if (str[i + 1] && str[i] == '=' && str[i + 1] == '=')
			*state_env = 3;
		i++;
	}
}

/*
** state_env validate arg to env variable
** 0 - didn't find equal char or forbidden char
** 1 - find first equal char
** 2 - find forbidden char
** 3 - find forbidden char before equal char or several equal on each other
** 4 - without forbidden chars and has one equal -> valid
*/

char			*get_str_to_compare(char **args, int *i, int *state_env)
{
	char			*str_to_compare;

	str_to_compare = ft_strdup("");
	while (args[*i] && ft_strcmp(args[*i], " "))
	{
		if (*state_env == 0 || *state_env == 2)
			verify_exe_create_env(args[*i], state_env);
		if (*state_env == 1 && args[*i][0] == '=')
			*state_env = 3;
		else if (*state_env == 1)
			*state_env = 4;
		concat_exe_arg(&str_to_compare,  args[*i]);
		*i += 1;
	}
	return (str_to_compare);
}

void			set_default_new_lst(t_exe_info **lst)
{
	(*lst)->next = NULL;
	(*lst)->exe_function = NULL;
	(*lst)->operator_exe_function = NULL;
	(*lst)->arg = ft_strdup("");
}