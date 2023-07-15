#include "shell.h"

/**
 * _Cp - copies A string.
 * @dest: The Destination.
 * @src: The source.
 * Return: pointer to destination
 */
char *_Cp(char *dest, char *src)
{
	int H = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[H])
	{
		dest[H] = src[H];
		H++;
	}
	dest[H] = 0;
	return (dest);
}

/**
 * _strdup_dupc_root - duplicates A str
 * @str: The str To Duplicate
 * Return: Ptr To the Duplicated str
 */
char *_str_dupc_root(const char *str)
{
	int length_one = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length_one++;
	ret = malloc(sizeof(char) * (length_one + 1));
	if (!ret)
		return (NULL);
	for (length_one++; length_one--;)
		ret[length_one] = *--str;
	return (ret);
}

/**
 * _puts - Print An input str.
 * @str: the str to be printed.
 * Return: Nothing.
 */
void _puts(char *str)
{
	int N = 0;

	if (!str)
		return;
	while (str[N] != '\0')
	{
		_putchar(str[N]);
		N++;
	}
}

/**
 * _putchar - Writes The Character C To stdout.
 * @c: The Character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int N;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || N >= WRITE_BUF_SIZE)
	{
		write(1, buf, N);
		N = 0;
	}
	if (c != BUF_FLUSH)
		buf[N++] = c;
	return (1);
}
