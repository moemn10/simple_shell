#include "shell.h"

/**
 * listing_Len - Determines Length OF Linked List.
 * @h: Pointer To First node.
 * Return: Size OF List.
 */
size_t listing_Len(const list_t *h)
{
	size_t Z = 0;

	while (h)
	{
		h = h->next;
		Z++;
	}
	return (Z);
}

/**
 * list_str - Returns An Arr Of Strings Of The List->str
 * @head: Pointer To First node.
 * Return: Arr of str.
 */
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t Z = listing_Len(head), x;
	char **strAll;
	char *str_one;

	if (!head || !Z)
		return (NULL);
	strAll = malloc(sizeof(char *) * (Z + 1));
	if (!strAll)
		return (NULL);
	for (Z = 0; node; node = node->next, Z++)
	{
		str_one = malloc(_strlen(node->str_one) + 1);
		if (!str_one)
		{
			for (x = 0; x < Z; x++)
				free(strAll[x]);
			free(strAll);
			return (NULL);
		}

		str_one = _strcpy(str, node->str_one);
		strAll[Z] = str_one;
	}
	strAll[Z] = NULL;
	return (strAll);
}


/**
 * out_list - Print All elements of a list_t linked list
 * @h: Pointer To First node
 *
 * Return: Size Of List
 */
size_t out_list(const list_t *h)
{
	size_t Z = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str_one ? h->str_one : "(nil)");
		_puts("\n");
		h = h->next;
		Z++;
	}
	return (Z);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_start(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start(node->str_one, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * Get_node - Gets the index of A node
 * @head: pointer To list head
 * @node: pointer To the ode
 *
 * Return: index of node or -1
 */
ssize_t Get_node(list_t *head, list_t *node)
{
	size_t Z = 0;

	while (head)
	{
		if (head == node)
			return (Z);
		head = head->next;
		Z++;
	}
	return (-1);
}
