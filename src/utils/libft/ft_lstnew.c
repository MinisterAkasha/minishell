#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *elem;

	if (!(elem = (t_list*)malloc(sizeof(t_list))))
		ft_error_malloc();
	elem->content = content;
	elem->next = NULL;
	return (elem);
}
