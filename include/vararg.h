#ifndef _VARARG_H
#define _VARARG_H

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char* MergeVaList(char *before, char *after, int count, va_list vl)
{
	if (count < 0) return NULL;

	// first char of final should be \0 for strcat() to work
	char *final = calloc(1, sizeof(char)); // free
	if (final == NULL) return NULL;

	size_t befLen = (before == NULL) ? 0 : strlen(before);
	size_t aftLen = (after == NULL) ? 0 : strlen(after);

	int i;
	for (i = 0; i < count; i++)
	{
		// get arg
		char *tmp = va_arg(vl, char*);
		if (tmp == NULL) continue;

		// resize string
		size_t newLen = strlen(final) + befLen + strlen(tmp) + aftLen + 1;

		final = realloc(final, newLen * sizeof(char));
		if (final == NULL) return NULL;

		// concatenate
		if (before != NULL) strcat(final, before);
		if (tmp != NULL) strcat(final, tmp);
		if (after != NULL) strcat(final, after);
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
