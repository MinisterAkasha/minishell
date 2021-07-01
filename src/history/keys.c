#include "minishell.h"

void	set_str_key_up(char **str_stat, t_history *history)
{
	clean_old_line(*str_stat);
	if (history->cur == history->total && history->is_new_str != 1 &&
		history->arr[history->cur])
	{
		free(*str_stat);
		(*str_stat) = ft_strdup(history->arr[history->cur]);
		history->is_new_str = 1;
	}
	else if (history->cur > 0 && history->arr[history->cur - 1])
	{
		free(history->arr[history->cur]);
		history->arr[history->cur] = ft_strdup(*str_stat);
		free(*str_stat);
		(*str_stat) = ft_strdup(history->arr[history->cur - 1]);
		history->cur--;
	}
	ft_putstr_fd(*str_stat, 1);
}

void	set_str_key_down(char **str_stat, t_history *history)
{
	clean_old_line(*str_stat);
	if (history->cur == history->total)
	{
		if (!history->is_new_str)
			create_new_history(history, *str_stat);
		else
		{
			free(*str_stat);
			(*str_stat) = ft_strdup(history->first_str);
		}
		history->is_new_str = 2;
	}
	else if (history->arr[history->cur] && history->arr[history->cur + 1])
	{
		free(history->arr[history->cur]);
		history->arr[history->cur] = ft_strdup(*str_stat);
		free(*str_stat);
		(*str_stat) = ft_strdup(history->arr[history->cur + 1]);
		history->cur++;
	}
	ft_putstr_fd(*str_stat, 1);
}

void	set_alpha(char **str_stat, char *buff, t_history *history)
{
	char	*joined_str;
	char	*copy_str_stat;
	char	*copy_buff;

	write(1, buff, ft_strlen(buff));
	copy_str_stat = ft_strdup((*str_stat));
	copy_buff = ft_strdup((buff));
	joined_str = ft_strjoin(copy_str_stat, copy_buff);
	free((*str_stat));
	(*str_stat) = ft_strdup(joined_str);
	if (history->total == history->cur)
	{
		free(history->first_str);
		history->first_str = ft_strdup((*str_stat));
	}
	free(copy_str_stat);
	free(copy_buff);
	free(joined_str);
}

void	delete_char(char **buff)
{
	int		len;

	len = ft_strlen((*buff));
	if (len > 0)
	{
		(*buff)[len - 1] = 0;
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
}
