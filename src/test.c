#include "garbage_collector.h"
#include "libft.h"
#include <stdlib.h>

int main()
{
	char *str = malloc2(sizeof(char) * 10);
	ft_bzero(str, 10);
	ft_strcpy(str, "coucou\n");
	write(1, str, 10);
	char *ptr = malloc(10000);
	trash_add(ptr, &free);
	trash_clear();
}
