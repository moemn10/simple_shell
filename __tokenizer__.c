#include "shell.h"

/**
 * **str_V_one - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_V_one(char *str, char *d)
{
	int z, w, l, y, chnum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (z = 0; str[z] != '\0'; z++)
		if (!is_dlim(str[z], d) && (is_dlim(str[z + 1], d) || !str[z + 1]))
			chnum++;

	if (chnum == 0)
		return (NULL);
	s = malloc((1 + chnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, w = 0; w < chnum; w++)
	{
		while (is_dlim(str[z], d))
			z++;
		l = 0;
		while (!is_dlim(str[z + l], d) && str[z + l])
			l++;
		s[w] = malloc((l + 1) * sizeof(char));
		if (!s[w])
		{
			for (l = 0; l < w; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (y = 0; y < l; y++)
			s[w][y] = str[z++];
		s[w][y] = 0;
	}
	s[w] = NULL;
	return (s);
}

/**
 * **str_V_Tow - split A str into Words
 * @str: The input str
 * @d: The delimeter
 * Return: A ptr To An Arr of strings, or NULL on failure
 */
char **str_V_Tow(char *str, char d)
{
	int z, w, l, y, chnum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (z = 0; str[z] != '\0'; z++)
		if ((str[z] != d && str[z + 1] == d) ||
				    (str[z] != d && !str[z + 1]) || str[z + 1] == d)
			chnum++;
	if (chnum == 0)
		return (NULL);
	s = malloc((1 + chnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (z = 0, w = 0; w < chnum; w++)
	{
		while (str[z] == d && str[z] != d)
			z++;
		l = 0;
		while (str[z + l] != d && str[z + l] && str[z + l] != d)
			l++;
		s[w] = malloc((l + 1) * sizeof(char));
		if (!s[w])
		{
			for (l = 0; l < w; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (y = 0; y < l; y++)
			s[w][y] = str[z++];
		s[w][y] = 0;
	}
	s[w] = NULL;
	return (s);
}
