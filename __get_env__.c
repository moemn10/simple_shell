#include "shell.h"

/**
 * geting_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **geting_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unseting_env - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unseting_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t r = 0;
	char *k;

	if (!node || !var)
		return (0);

	while (node)
	{
		k = start_data(node->str, var);
		if (k && *k == '=')
		{
			info->env_changed = deleting_node_index(&(info->env), r);
			r = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		r++;
	}
	return (info->env_changed);
}

/**
 * _seting_env - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _seing_tenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *k;

	if (!var || !value)
		return (0);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_Cp(buf, var);
	_Cp(buf, "=");
	_str_dot(buf, value);
	node = info->env;
	while (node)
	{
		k = start_data(node->str, var);
		if (k && *k == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	adding_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
