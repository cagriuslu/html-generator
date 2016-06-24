#include <stdio.h>

#include <html.h>
#include <vararg.h>

int main()
{
	char *th1 = HtmlTag("th", NULL, 1, "Month");
	char *th2 = HtmlTag("th", NULL, 1, "Savings");

	char *td1 = HtmlTag("td", NULL, 1, "January");
	char *td2 = HtmlTag("td", NULL, 1, "$100");

	char *tr1 = HtmlTag("tr", NULL, 2, th1, th2);
	char *tr2 = HtmlTag("tr", NULL, 2, td1, td2);

	char *table = HtmlTag("table", NULL, 2, tr1, tr2);

	char *head = HtmlTag("head", NULL, 0);
	char *body = HtmlTag("body", NULL, 1, table);

	char *html = HtmlTag("html", NULL, 2, head, body);

	char *doc = Merge(NULL, NULL, 2, "<!DOCTYPE html>", html);

	printf("%s\n", doc);
	
	return 0;
}
