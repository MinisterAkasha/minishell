#include "libft.h"

void	ft_error_malloc(void)
{
	printf("Error: Malloc can't allocate memory \n%s\n", strerror(errno));
	exit(1);
}
