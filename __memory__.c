#include "shell.h"

/**
 * Sysdb - frees A Pointer and NULLs the address.
 * @ptr: address Of The pointer To free
 *
 * Return: 1 if freed, otherwise 0.
 */
int Sysdb(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
