#include "shell.h"

/**
 * clearing_info - initializes info_t struct
 * @info: struct address
 */
void clearing_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * seting_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void seting_info(info_t *info, char **av)
{
	int r = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_V_one(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _str_dupc_root(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (r = 0; info->argv && info->argv[r]; r++)
			;
		info->argc = r;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * fr_info - frees info_t struct fields
 * @info: struct address
 * @A: true if freeing all fields
 */
void fr_info(info_t *info, int A)
{
	dbfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (A)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fr_list(&(info->env));
		if (info->history)
			fr_list(&(info->history));
		if (info->alias)
			fr_list(&(info->alias));
		dbfree(info->environ);
			info->environ = NULL;
		Sysdb((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
