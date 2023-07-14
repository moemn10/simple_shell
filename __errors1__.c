#include "shell.h"

/**
 * _erputs - printing an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _erputs(char *str)
{
	int r = 0;

	if (!str)
		return;
	while (str[r] != '\0')
	{
		_erputchar(str[r]);
		r++;
	}
}

/**
 * _erputchar - writing the character c to stderr
 * @x: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _erputchar(char x)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(2, buf, r);
		r = 0;
	}
	if (x != BUF_FLUSH)
		buf[r++] = x;
	return (1);
}

/**
 * _putfd_ - writes the character c to given fd
 * @x: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd_(char x, int fd)
{
	static int r;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || r >= WRITE_BUF_SIZE)
	{
		write(fd, buf, r);
		r = 0;
	}
	if (x != BUF_FLUSH)
		buf[r++] = x;
	return (1);
}

/**
 * _putsfd_ - printing an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd_(char *str, int fd)
{
	int r = 0;

	if (!str)
		return (0);
	while (*str)
	{
		r += _putfd_(*str++, fd);
	}
	return (r);
}
