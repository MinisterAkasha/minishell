/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tilda <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 15:43:21 by tilda             #+#    #+#             */
/*   Updated: 2021/03/20 15:43:23 by tilda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

char	*init_terminal_data()
{
	char *term_buffer;
	char *termtype = getenv("TERM");//TODO get from env
	int success;

	term_buffer = (char *)malloc(sizeof(char) * 2048);//TODO free and protect
	printf("Init_terminal_data\n");
	if (termtype == 0)
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");

	success = tgetent(term_buffer, termtype);
	if (success > 0)
		printf("termtype: %s\nterm_buffer: %s\nsuccess: %d\n", termtype, term_buffer, success);
	else
	{
		printf("Error: The result: %d\n", success);
		exit(1);
	}
	printf("\n");
	return term_buffer;
}


void	interrogate_terminal(char *term_buffer)
{
	char *temp;
	char *cl_string, *cm_string;
	int height;
	int width;
	int auto_wrap;
	char *buffer;

	char PC;   /* For tputs.  */
	char *BC;  /* For tgoto.  */
	char *UP;

	buffer = (char *)malloc(sizeof(char) * strlen(term_buffer));
	printf("Interrogate_terminal\n");
	/* Extract information we will use.  */
	cl_string = tgetstr ("cl", &buffer);
	printf("buffer: %s\n", buffer);
	cm_string = tgetstr ("cm", &buffer);
	auto_wrap = tgetflag ("am");
	height = tgetnum ("li");
	width = tgetnum ("co");

	/* Extract information that termcap functions use.  */
	temp = tgetstr ("pc", &buffer);
	PC = temp ? *temp : 0;
	BC = tgetstr ("le", &buffer);
	UP = tgetstr ("up", &buffer);

	printf("cl_string: %s\n", cl_string);
	printf("cm_string: %s\n", cm_string);
	printf("auto_wrap: %d\n", auto_wrap);
	printf("height: %d\n", height);
	printf("width: %d\n", width);
	printf("temp: %s\n", temp);
	printf("PC: %c\n", PC);
	printf("BC: %s\n", BC);
	printf("UP: %s\n", UP);
}

//void	delete_char(char **str)
//{
//	int		len;
//
//	len = strlen(*str);
//	*str[len] = 0;
//}


int main()
{
	char	*str;
	int		len;
	struct	termios term;
	char	*buf_tmp;
	char	*result;


	len = 1;
	result = calloc(sizeof(char) , 2048);
	str = calloc(sizeof(char), 2048);
	while (strcmp(str, "\4"))
	{
		tcgetattr(0, &term);
		term.c_lflag &= ~(ECHO);
		term.c_lflag &= ~(ICANON);
		tcsetattr(0, TCSANOW, &term);
		tgetent(0, getenv("TERM"));
		write(1, save_cursor, strlen(save_cursor));
		do
		{
			free(str);
			str = calloc(sizeof(char), 2048);
			buf_tmp = ft_strdup(result);
			free(result);
			len = read(0, str, 100);
			str[len] = 0;
			if (!strcmp(str, "\e[A"))
			{
				write(1, restore_cursor, strlen(restore_cursor));
				write(1, delete_line, strlen(delete_line));
				write(1, "up", 2);
			} else if (!strcmp(str, "\e[B"))
			{
				write(1, restore_cursor, strlen(restore_cursor));
				write(1, delete_line, strlen(delete_line));
				write(1, "down", 4);
			} else if (!strcmp(str, "\177"))
			{
				write(1, cursor_left, strlen(cursor_left));
				write(1, delete_character, strlen(delete_character));
				delete_char(&buf_tmp);
			} else
			{
				result = ft_strjoin(buf_tmp, str);
				write(1, str, len);
			}
			free(buf_tmp);

		} while (strcmp(str, "\n") && strcmp(str, "\4"));

		term.c_lflag |= ~(ECHO);
		term.c_lflag |= ~(ICANON);
//		ft_putendl_fd("Result\n", 1);
//		write(1, result, strlen(result));
//		write(1, "\n", 1);
	}
	ft_putendl_fd("Final result", 1);
	ft_putendl_fd(result, 1);
	return 0;
}