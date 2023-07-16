#include "shell.h"

/**
 **_strncpy - copy a string
 *@dest: the destination of string to be copied to
 *@src: the source of string
 *@m: the amount of char to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int m)
{
	int r, q;
	char *h = dest;

	r = 0;
	while (src[r] != '\0' && r < m - 1)
	{
		dest[r] = src[r];
		r++;
	}
	if (r < m)
	{
		q = r;
		while (q < m)
		{
			dest[q] = '\0';
			q++;
		}
	}
	return (h);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int r, q;
	char *h = dest;

	r = 0;
	q = 0;
	while (dest[r] != '\0')
		r++;
	while (src[q] != '\0' && q < m)
	{
		dest[r] = src[q];
		r++;
		q++;
	}
	if (q < m)
		dest[r] = '\0';
	return (h);
}

/**
 **_strchr - locates a character in a string
 *@h: the string to be parsed
 *@x: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *h, char x)
{
	do {
		if (*h == x)
			return (h);
	} while (*h++ != '\0');

	return (NULL);
}
