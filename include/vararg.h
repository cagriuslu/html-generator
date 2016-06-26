#ifndef _VARARG_H
#define _VARARG_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char* Merge(int count, ...) 
{
	if (count < 0) return NULL;

	// first char of str should be \0 for strcat to work
	char *final = calloc(1, 1);
	if (!final) return NULL;
	
	va_list vl;
	va_start(vl, count);
	for (int i = 0; i < count; i++)
	{
		char *tmp = va_arg(vl, char*);
		if (!tmp) continue;

		// resize
		size_t len = strlen(final) + strlen(tmp) + 1;
		final = realloc(final, len * sizeof(char));
		if (!final)
		{
			va_end(vl);
			return NULL;
		}

		strcat(final, tmp);
	}
	
	va_end(vl);
	return final;
}

#endif

