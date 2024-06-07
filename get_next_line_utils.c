#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	max_size;

	if (count == 0 || size == 0)
		return (malloc(0));
	total_size = count * size;
	max_size = (size_t)-1;
	if (count && size && count > (UINT_MAX / size))
	{
		errno = ENOMEM;
		return (NULL);
	}
	ptr = (void *)malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}