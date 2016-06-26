#include <stdio.h>

#include <html.h>
#include <vararg.h>

int main()
{
	char *tr1d1Attr = HtmlAttr(1, "colspan", "2");
	char *tr1d1 = HtmlTag("td", tr1d1Attr, 1, "Person");
	
	char *tr2d1 = HtmlTag("td", NULL, 1, "Name:");
	char *tr2d2 = HtmlTag("td", NULL, 1, "Cagri");
	
	char *tr3d1 = HtmlTag("td", NULL, 1, "Age:");
	char *tr3d2 = HtmlTag("td", NULL, 1, "22");
	
	char *tr1 = HtmlTag("tr", NULL, 1, tr1d1);
	char *tr2 = HtmlTag("tr", NULL, 2, tr2d1, tr2d2);
	char *tr3 = HtmlTag("tr", NULL, 2, tr3d1, tr3d2);
	
	char *tableAttr = HtmlAttr(1, "border", "1");
	char *table = HtmlTag("table", tableAttr, 3, tr1, tr2, tr3);
	
	char *title = HtmlTag("title", NULL, 1, "Person Table");
	char *head = HtmlTag("head", NULL, 1, title);
	char *body = HtmlTag("body", NULL, 1, table);
	
	char *html = HtmlTag("html", NULL, 2, head, body);
	
	char *doc = Merge(NULL, NULL, 2, "<!DOCTYPE html>\r\n", html);
	
	printf("%s\n", doc);
	
	return 0;
}
