#include <stdio.h>

#include <html.h>
#include <vararg.h>

int main()
{
	char *t = Merge(NULL, NULL, 1, "");
	printf("%s\n", t);
	
	return 0;
}
