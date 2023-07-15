#include "shell.h"

/**
 * _mset - Fills Memory with A Constant byte
 * @s: The Pointer To The Memory area
 * @b: The byte to Fill *s with
 * @n: The Amount of bytes To Be Filled
 * Return: (s) a pointer to the memory area s
 */
char *_mset(char *s, char b, unsigned int n)
{
	unsigned int C;

	for (C = 0; C < n; C++)
		s[C] = b;
	return (s);
}

/**
 * dbfree - frees a string of strings
 * @pp: string of strings
 */
void dbfree(char **pp)
{
	char **L = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(L);
}

/**
 * _lloc - Reallocates A block Of memory
 * @ptr: pointer to prev malloc'ated block
 * @old_size: Byte Size Of prev block
 * @new_size: Byte Size Of New block
 * Return: pointer to da ol'block nameen.
 */
void *_lloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *U;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	U = malloc(new_size);
	if (!U)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		U[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (U);
}
