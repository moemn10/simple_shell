#include "shell.h"

/**
 * my_history - Displaying the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(info_t *info)
{
	out_list(info->history);
	return (0);
}

/**
 * _unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(info_t *info, char *str)
{
	char *k, x;
	int rt;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	x = *k;
	*k = 0;
	rt = deleting_node_index(&(info->alias),
		Get_node(info->alias, node_start(info->alias, str, -1)));
	*k = x;
	return (rt);
}

/**
 * seting_alias - Seting alias to string
 * @info: Parameter struct
 * @str: The string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int seting_alias(info_t *info, char *str)
{
	char *k;

	k = _strchr(str, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (_unset_alias(info, str));

	_unset_alias(info, str);
	return (adding_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printing_alias - Printing an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printing_alias(list_t *node)
{
	char *k = NULL, *z = NULL;

	if (node)
	{
		k = _strchr(node->str, '=');
		for (z = node->str; z <= k; z++)
		_putchar(*z);
		_putchar('\'');
		_puts(k + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int r = 0;
	char *k = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printing_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (r = 1; info->argv[r]; r++)
	{
		k = _strchr(info->argv[r], '=');
		if (k)
			seting_alias(info, info->argv[r]);
		else
			printing_alias(node_start(info->alias, info->argv[r], '='));
	}

	return (0);
}
