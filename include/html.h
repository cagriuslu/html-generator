#ifndef _HTML_H
#define _HTML_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <vararg.h>

char* HtmlAttr(int count, ...)
{
	if (count < 0) return NULL;

	char *attr = NULL;
	
	// merge attributes
	va_list vl;
	va_start(vl, count);
	for (int i = 0; i < count; i++)
	{
		char *key = va_arg(vl, char*);
		char *value = va_arg(vl, char*);
		
		attr = Merge(NULL, NULL, 5,
			attr,
			key,
			key ? "=\"" : NULL,
			value,
			key ? "\" " : " ");
	}
	va_end(vl);

	// if attr is not empty rmv last space
	if (attr[0] != '\0') attr[strlen(attr) - 1] = '\0';

	return attr;
}

char* HtmlTag(char *type, char *attr, int count, ...)
{
	// get contents
	va_list vl;
	va_start(vl, count);
	char *content = MergeVaList(NULL, "\r\n", count, vl);
	va_end(vl);
	if (!content) return NULL;
	
	// print type and attributes, if any
	char *tag = Merge(NULL, NULL, 5,
		"<",
		type,
		attr ? " " : NULL,
		attr,
		">\r\n");
	
	// add indent while printing contents
	int i = 0;
	while (1)
	{
		char *lnBreak = strstr(content + i, "\r\n");
		if (!lnBreak) break;
		
		lnBreak[0] = '\0';
		lnBreak[1] = '\0';

		tag = Merge(NULL, NULL, 4, tag, "\t", content + i, "\r\n");
		i += lnBreak - (content+i) + 2;
	}
	free(content);
	
	// print closing tag and return
	return Merge(NULL, NULL, 4, tag, "</", type, ">");
}

char* HtmlEmptyTag(char *type, char *attr)
{
	return Merge(NULL, NULL, 5,
		"<",
		type,
		attr ? " " : NULL,
		attr,
		">");
}

#endif
