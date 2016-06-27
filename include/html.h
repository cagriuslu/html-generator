#ifndef _HTML_H
#define _HTML_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <vararg.h>

char* HtmlTag(char *type, char *attr, int count, ...)
{
	// get contents
	va_list vl;
	va_start(vl, count);
	char *content = NULL;
	for (int i = 0; i < count; i++) content = Concat(3, content, va_arg(vl, char*), "\r\n");
	va_end(vl);
	if (!content) return NULL;
	
	// print type and attributes, if any
	char *tag = Concat(5, "<", type, attr ? " " : NULL, attr, ">\r\n");
	
	// add indent while printing contents
	int i = 0;
	while (1)
	{
		char *lnBreak = strstr(content + i, "\r\n");
		if (!lnBreak) break;
		
		lnBreak[0] = '\0';
		lnBreak[1] = '\0';

		tag = Concat(4, tag, "\t", content + i, "\r\n");
		i += lnBreak - (content+i) + 2;
	}
	free(content);
	
	// print closing tag and return
	return Concat(4, tag, "</", type, ">");
}

char* HtmlEmptyTag(char *type, char *attr)
{
	return Concat(5, "<", type, attr ? " " : NULL, attr, ">");
}

#endif

