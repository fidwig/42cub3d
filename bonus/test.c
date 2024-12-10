typedef struct s_test
{
	int arr[7];
	char s[4];
	int x;
	char c;
}				t_t;

#include <string.h>
#include <stdio.h>
int main()
{
	t_t test;

	for (int i = 0; i < 7; i++)
		test.arr[i] = i;
	strncpy(test.s, "abc", 4);
	test.x = 23;
	test.c = 'g';
	void *p;

	p = test.arr;
	for (int i = 0; i < 7; i++)
	{
		printf("%d ", *((int *)p));
		p += sizeof(int);
	}
	printf("\n");
	printf("<%s>\n", (char *)p);
	p += sizeof(char) * 4;
	printf("x = %d\n", *((int *)p));
	p += sizeof(int);
	printf("c = %c\n", *((char *)p));
	return (0);
}
