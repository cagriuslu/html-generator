#ifndef _VARARG_H
#define _VARARG_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char* MergeVaList(char *before, char *after, int count, va_list vl)
{
	if (count < 0) return NULL;

	// first char of str should be \0 for strcat to work
	char *final = calloc(1, 1);
	if (!final) return NULL;

	size_t befLen = (!before) ? 0 : strlen(before);
	size_t aftLen = (!after)  ? 0 : strlen(after);

	for (int i = 0; i < count; i++)
	{
		// get arg
		char *tmp = va_arg(vl, char*);
		if (!tmp) continue;

		// resize final
		size_t len = strlen(final) + befLen + strlen(tmp) + aftLen + 1;
		final = realloc(final, len * sizeof(char));
		if (!final) return NULL;

		// concatenate
		if (before) strcat(final, before);
		if (tmp)    strcat(final, tmp);
		if (after)  strcat(final, after);
	}

	return final;
}

char* Merge(char *before, char *after, int count, ...)
{
	if (count < 0) return NULL;

	va_list vl;
	va_start(vl, count); // va_end
	char *final = MergeVaList(before, after, count, vl);
	va_end(vl);

	return final;
}

#endif
