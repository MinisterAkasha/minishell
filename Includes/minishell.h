/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akasha <akasha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:01:35 by akasha            #+#    #+#             */
/*   Updated: 2021/03/08 19:49:29 by akasha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>

# include <sys/types.h>
# include <sys/wait.h>

# include "get_next_line.h"
# include "../src/utils/libft/includes/libft.h"

typedef struct	s_data
{
	char		**env;
	char		**argv;
}				t_data;


#endif