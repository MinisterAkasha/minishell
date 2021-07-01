#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	if (!s1)
		return (NULL);
	dup = (char *)malloc((ft_strlen(s1) * sizeof(char)) + 1);
	i = 0;
	if (!dup)
		ft_error_malloc();
	while (i < ft_strlen(s1))
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}
