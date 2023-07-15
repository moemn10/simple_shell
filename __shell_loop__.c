#include "shell.h"

/**
 * mkw - Main shell loop
 * @info: The parameter And Return Info Struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int mkw(info_t *info, char **av)
{
	ssize_t Y = 0;
	int bin = 0;

	while (Y != -1 && bin != -2)
	{
		clearing_info(info);
		if (inactive(info))
			_puts("$ ");
		_erputchar(BUF_FLUSH);
		Y = get_in(info);
		if (Y != -1)
		{
			seting_info(info, av);
			bin = search_built(info);
			if (bin == -1)
				find_lin(info);
		}
		else if (inactive(info))
			_putchar('\n');
		fr_info(info, 0);
	}
	writing_history(info);
	fr_info(info, 1);
	if (!inactive(info) && info->status)
		exit(info->status);
	if (bin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (bin);
}

/**
 * search_built - find A builtin command
 * @info: the parameter And Return about struct
 *
 * Return: -1 if builtin Not Found,
 * 	0 if builtin Executed Successfully,
 * 	1 if builtin Found but Not Successful,
 * 	2 if builtin Signals exit()
 */
int search_built(info_t *info)
{
	int X, ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (X = 0; builtintbl[X].type; X++)
		if (_strgo(info->argv[0], builtintbl[X].type) == 0)
		{
			info->line_count++;
			ret = builtintbl[X].func(info);
			break;
		}
	return (ret);
}

/**
 * find_lin - find A Command in PATH
 * @info: the parameter And return info struct
 * Return: void
 */
void find_lin(info_t *info)
{
	char *path = NULL;
	int W, V;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (W = 0, V = 0; info->arg[W]; W++)
		if (!is_dlim(info->arg[W], " \t\n"))
			V++;
	if (!V)
		return;

	path = search(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_Command(info);
	}
	else
	{
		if ((inactive(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && linux_command(info, info->argv[0]))
			fork_Command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printing_error(info, "not found\n");
		}
	}
}

/**
 * fork_Command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_Command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: but ERROR func */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, geting_environ(info)) == -1)
		{
			fr_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: but ERROR func */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printing_error(info, "Permission denied\n");
		}
	}
}
