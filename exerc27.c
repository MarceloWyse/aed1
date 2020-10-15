#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void* memcpy(void* destination, const void source, size_t)

void* meurealloc(void* p, size_t t);

int main()
{
	int* p = (int*) malloc(sizeof(int));

	p = meurealloc(p, 100);
	
	free(p);
	return 0;
}

void* meurealloc(void* p, size_t t)
{
	void* m;
	m = malloc(t);
	
	memcpy(m, p, sizeof(p));
	
	free(p);
	
	return m;
}