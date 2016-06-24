#ifndef _HTML_H
#define _HTML_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <vararg.h>

char* HtmlAttr(int count, ...)
{
	if (count < 0) return NULL;

	va_list vl;
	va_start(vl, count); // va_end

	char *attr = calloc(1, sizeof(char)); // free
	if (attr == NULL)
	{
		va_end(vl);
		return NULL;
	}

	int i;
	for (i = 0; i < count; i++)
	{
		char *key = va_arg(vl, char*);
		char *value = va_arg(vl, char*);
		
		size_t attrLen;

		if (key == NULL && value == NULL) continue;
		else if (key == NULL && value) attrLen = strlen(attr) + strlen(value) + 2;
		else if (key && value == NULL) attrLen = strlen(attr) + strlen(key) + 5;
		else attrLen = strlen(attr) + strlen(key) + 2 + strlen(value) + 3;

		attr = realloc(attr, attrLen * sizeof(char));
		if (attr == NULL)
		{
			va_end(vl);
			return NULL;
		}

		if (key) strcat(attr, key);
		if (key) strcat(attr, "=\"");
		if (value) strcat(attr, value);
		if (key) strcat(attr, "\"");
		strcat(attr, " ");
	}

	// remove unnecessary space
	size_t attrLen = strlen(attr);
	if (attrLen > 0) attr[attrLen - 1] = '\0';

	va_end(vl);
	return attr;
}

char* HtmlTag(char *type, char *attr, int count, ...)
{
	if (type == NULL) return NULL;
	
	// print tag type
	char *tag = calloc(1 + strlen(type) + 1, sizeof(char)); // free
	if (tag == NULL) return NULL;
	strcat(tag, "<");
	strcat(tag, type);
	
	// print attributes
	if (attr)
	{
		tag = realloc(tag, strlen(tag) + 1 + strlen(attr) + 2);
		if (tag == NULL) return NULL;

		strcat(tag, " ");
		strcat(tag, attr);
		strcat(tag, ">");
	}
	else
	{
		tag = realloc(tag, strlen(tag) + 2);
		if (tag == NULL) return NULL;

		strcat(tag, ">");
	}
	
	// print content
	va_list vl;
	va_start(vl, count); // va_end
	char *content = MergeVaList(NULL, NULL, count, vl); // free
	va_end(vl);
	if (content == NULL)
	{
		free(tag);
		return NULL;
	}

	tag = realloc(tag, strlen(tag) + strlen(content) + 2 + strlen(type) + 2);
	if (tag == NULL)
	{
		free(content);
		return NULL;
	}

	strcat(tag, content);
	free(content);

	// print closing tag
	strcat(tag, "</");
	strcat(tag, type);
	strcat(tag, ">");

	return tag;
}

char* HtmlEmptyTag(char *type, char *attr)
{
	if (type == NULL) return NULL;
	
	// print tag type
	char *tag = calloc(1 + strlen(type) + 1, sizeof(char)); // free
	if (tag == NULL) return NULL;
	strcat(tag, "<");
	strcat(tag, type);
	
	// print attributes
	if (attr)
	{
		tag = realloc(tag, strlen(tag) + 1 + strlen(attr) + 2);
		if (tag == NULL) return NULL;

		strcat(tag, " ");
		strcat(tag, attr);
		strcat(tag, ">");
	}
	else
	{
		tag = realloc(tag, strlen(tag) + 2);
		if (tag == NULL) return NULL;

		strcat(tag, ">");
	}
	
	return tag;
}

#endif
