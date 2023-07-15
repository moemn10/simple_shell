#include "shell.h"

/**
 * in_buf - buffering chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t in_buf(info_t *info, char **buf, size_t *l)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*l) /* **if nothing left in the buffer, fill it** */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigin_Handler);
#if USE_GETLINE
		i = getline(buf, &len_p, stdin);
#else
		i = _geting_line(info, buf, &len_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0'; /* removing trailing newline */
				i--;
			}
			info->linecount_flag = 1;
			rm_com(*buf);
			building_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*l = i;
				info->cmd_buf = buf;
			}
		}
	}
	return (i);
}

/**
 * get_in - geting a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_in(info_t *info)
{
	static char *buf; /* **the poly ';' command chain buffer** */
	static size_t r, q, l;
	ssize_t i = 0;
	char **buf_p = &(info->arg), *k;

	_putchar(BUF_FLUSH);
	i = in_buf(info, &buf, &l);
	if (i == -1) /* **EOF** */
		return (-1);
	if (l) /* **We have commands left in the chain buff */
	{
		q = r; /* **Init new iterator to current buf pos** */
		k = buf + r; /* **Get pointer for return** */

		check_bbc(info, buf, &q, r, l);
		while (q < l) /* **Iterate to semicolon or end** */
		{
			if (bbc(info, buf, &q))
				break;
			q++;
		}

		r = q + 1; 
		if (r >= l) 
		{
			r = l = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = k; 
		return (_strlength(k)); 
	}

	*buf_p = buf; 
	return (i); 
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _geting_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _geting_line(info_t *info, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t r, l;
	size_t p;
	ssize_t i = 0, h = 0;
	char *k = NULL, *new_p = NULL, *x;

	k = *ptr;
	if (k && len)
		h = *len;
	if (r == l)
		r = l = 0;

	i = read_buf(info, buf, &l);
	if (i == -1 || (i == 0 && l == 0))
		return (-1);

	x = _strchr(buf + r, '\n');
	p = x ? 1 + (unsigned int)(x - buf) : l;
	new_p = _lloc(k, h, h ? h + p : p + 1);
	if (!new_p) /* MALLOC F! */
		return (k ? free(k), -1 : -1);

	if (h)
		_strncat(new_p, buf + r, p - r);
	else
		_strncpy(new_p, buf + r, p - r + 1);

	h += p - r;
	r = p;
	k = new_p;

	if (len)
		*len = h;
	*ptr = k;
	return (h);
}

/**
 * sigin_Handler - blocks ctrl-C
 * @sig_n: the signal number
 *
 * Return: void
 */
void sigin_Handler(__attribute__((unused))int sig_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
