#include "shell.h"

/**
 * my_env - Printing the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	printing_list_str(info->env);
	return (0);
}

/**
 * get_env - Geting the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment var name
 *
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *k;

	while (node)
	{
		k = start_data(node->str, name);
		if (k && *k)
			return (k);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set_env - Initializinh a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_erputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_seting_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - Removing an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int my_unset_env(info_t *info)
{
	int r;

	if (info->argc == 1)
	{
		_erputs("Too few arguements.\n");
		return (1);
	}
	for (r = 1; r <= info->argc; r++)
		_unseting_env(info, info->argv[r]);

	return (0);
}

/**
 * pop_env_list - populating env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t r;

	for (r = 0; environ[r]; r++)
		adding_node_end(&node, environ[r], 0);
	info->env = node;
	return (0);
}
