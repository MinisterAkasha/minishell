/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:19:30 by akasha            #+#    #+#             */
/*   Updated: 2021/03/13 18:54:20 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl(char **env)
{
	char	*lvl;
	int		current_shlvl;

	current_shlvl = ft_atoi(ft_strchr(get_env_param("SHLVL", env), '=') + 1);
	lvl = ft_itoa(current_shlvl + 1);
	change_env(lvl, "SHLVL", &env);
	free(lvl);
}