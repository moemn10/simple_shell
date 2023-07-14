#include "shell.h"

/**
 * inactive - returning true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int inactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_dlim - Checking if character is a delimeter
 * @x: the charcter to check
 * @dlim: the delimeter's string
 * Return: 1 if true, 0 if false
 */
int is_dlim(char x, char *dlim)
{
	while (*dlim)
		if (*dlim++ == x)
			return (1);
	return (0);
}

/**
 * is_alpha - Checking for alphabetic character
 * @x: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * __atoi - Converting a string to an integer
 * @h: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int __atoi(char *h)
{
	int r, sg = 1, fg = 0, output;
	unsigned int result = 0;

	for (r = 0; h[r] != '\0' && fg != 2; r++)
	{
		if (h[r] == '-')
			sg *= -1;

		if (h[r] >= '0' && h[r] <= '9')
		{
			fg = 1;
			result *= 10;
			result += (h[r] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sg == -1)
		output = -result;
	else
		output = result;

	return (output);
}
