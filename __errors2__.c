#include "shell.h"

/**
 * _erratoi_ - Converting a string to an integer
 * @h: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi_(char *h)
{
	int r = 0;
	unsigned long int result = 0;

	if (*h == '+')
		h++;  /* TODO: WHY does This Make Main Return 255? */
	for (r = 0;  h[r] != '\0'; r++)
	{
		if (h[r] >= '0' && h[r] <= '9')
		{
			result *= 10;
			result += (h[r] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printing_error - printing an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printing_error(info_t *info, char *estr)
{
	_erputs(info->fname);
	_erputs(": ");
	printing_d(info->line_count, STDERR_FILENO);
	_erputs(": ");
	_erputs(info->argv[0]);
	_erputs(": ");
	_erputs(estr);
}

/**
 * printing_d - Function prints a decimal (integer) number (base 10)
 * @in:  input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printing_d(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int r, ct = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _erputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (r = 1000000000; r > 1; r /= 10)
	{
		if (_abs_ / r)
		{
			__putchar('0' + current / r);
			ct++;
		}
		current %= r;
	}
	__putchar('0' + current);
	ct++;

	return (ct);
}

/**
 * converting_number - convertering function, a clone of itoa
 * @n: number
 * @base: base
<<<<<<< HEAD
 * @flags: argument Flags
=======
 * @fg: argument flags
>>>>>>> ac58511b78e35a7504d0ab64c299cca128f7aa93
 *
 * Return: string
 */
char *converting_number(long int n, int base, int fg)
{
	static char *array;
	static char buffer[50];
	char sg = 0;
	char *ptr;
	unsigned long m = n;

	if (!(fg & CONVERT_UNSIGNED) && n < 0)
	{
		m = -n;
		sg = '-';

	}
	array = fg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % base];
		m /= base;
	} while (m != 0);

	if (sg)
		*--ptr = sg;
	return (ptr);
}

/**
 * rm_com - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_com(char *buf)
{
	int r;

	for (r = 0; buf[r] != '\0'; r++)
		if (buf[r] == '#' && (!r || buf[r - 1] == ' '))
		{
			buf[r] = '\0';
			break;
		}
}
