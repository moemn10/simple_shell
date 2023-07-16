#include "shell.h"

/**
 * _strlength - Return The length of A String
 * @s: The string Whose length To check
 *
 * Return: integer length of string
 */
int _strlength(char *s)
{
	int D = 0;

	if (!s)
		return (0);

	while (*s++)
		D++;
	return (D);
}

/**
 * _strgo - Performs lexicogarphic comparison Of Two strangs.
 * @s1: The First Strang.
 * @s2: The Second Strang.
 * Return: Negative if s1 < s2, Positive if s1 > s2, Zero if s1 == s2
 */
int _strgo(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_data - Checks If need To start With haystack
 * @haystack: String To Search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_data(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _str_dot - Concatenates 2 strings
 * @dest: The Destination buff
 * @src: The Source buff
 * Return: Pointer To destination buff
 */
char *_str_dot(char *dest, char *src)
{
	char *res = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (res);
}
