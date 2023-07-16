#include "shell.h"

/**
 * linux_command - determines if A File is An executable command.
 * @info: The info struct
 * @path: Path To the file
 * Return: 1 if true, 0 otherwise
 */
int linux_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * db_ch - Duplicates Characters.
 * @pathstr: The PATH str.
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *db_ch(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int Q = 0, T = 0;

	for (T = 0, Q = start; stop > Q; Q++)
		if (pathstr[Q] != ':')
			buf[T++] = pathstr[Q];
	buf[T] = 0;
	return (buf);
}

/**
 * search - search this command prompt in The PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *search(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, var = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlength(cmd) > 2) && start_data(cmd, "./"))
	{
		if (linux_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = db_ch(pathstr, var, i);
			if (!*path)
				_str_dot(path, cmd);
			else
			{
				_str_dot(path, "/");
				_str_dot(path, cmd);
			}
			if (linux_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			var = i;
		}
		i++;
	}
	return (NULL);
}
