#include "shell.h"

/**
 * geting_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *geting_history_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlength(dir) + _strlength(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_Cp(buf, dir);
	_str_dot(buf, "/");
	_str_dot(buf, HIST_FILE);
	return (buf);
}

/**
 * writing_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int writing_history(info_t *info)
{
	ssize_t fd;
	char *filename = geting_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd_(node->str, fd);
		_putfd_('\n', fd);
	}
	_putfd_(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * reading_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int reading_history(info_t *info)
{
	int r, last = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = geting_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (r = 0; r < fsize; r++)
		if (buf[r] == '\n')
		{
			buf[r] = 0;
			building_history_list(info, buf + last, lc++);
			last = r + 1;
		}
	if (last != r)
		building_history_list(info, buf + last, lc++);
	free(buf);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		deleting_node_index(&(info->history), 0);
	renumbering_history(info);
	return (info->histcount);
}

/**
 * building_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @lc: the history linecount, histcount
 *
 * Return: Always 0
 */
int building_history_list(info_t *info, char *buf, int lc)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	adding_node_end(&node, buf, lc);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumbering_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumbering_history(info_t *info)
{
	list_t *node = info->history;
	int r = 0;

	while (node)
	{
		node->num = r++;
		node = node->next;
	}
	return (info->histcount = r);
}
