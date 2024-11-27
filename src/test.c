#include "garbage_collector.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	char *end;
	long long n = ft_strtoll("12    ,123", &end, 10);
	printf("n = %lld, end = <%s>\n", n, end);
}
