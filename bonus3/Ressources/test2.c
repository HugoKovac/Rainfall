#include <stdio.h>
int main(int ac, char **av){
	printf("ac : %d\n", ac);
	for (int i = 1; i < ac; i++)
		printf("ac[%d] = %s\n", i, av[i]);
}