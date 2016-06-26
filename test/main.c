#include <stdio.h>

#include <html.h>
#include <vararg.h>

int main()
{
	char *t1 = HtmlTag("tag", NULL, 1, "abc");
	char *t2 = HtmlTag("tag", NULL, 1, t1);
	
	printf("%s\n", t2);
	
	return 0;
}
