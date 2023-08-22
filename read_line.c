#include "shell.h"

/**
 * read_buf - reads a buffer
 * @info: info struct
 * @buf: buffer
 * @size: new size (will be overridden)
 *
 * Return: size of read bytes
 */

ssize_t read_buf(info_t *info, char *buf, size_t *size)
{
	ssize_t l = 0;

	if (*size)
		return (0);

	l = read(info->readfd, buf, BUF_SIZE);

	if (l >= 0)
		*size = l;
	return (l);
}

/**
 * _getline - gets input line from STDIN
 * @info: info struct
 * @pBuf: address of pointer to buffer
 * @length: length of Buffer
 *
 * Return: actual number of bytes read
 */

int _getline(info_t *info, char **pBuf, size_t *length)
{
	static char buf[BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pBuf;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*pBuf = p;
	return (s);
}

/**
 * input_buf - buffers chained commands
 * @info: info struct
 * @buf: buffer addr
 * @len: length addr
 *
 * Return: number of bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = _getline(info, buf, &len_p);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * sigintHandler - handles ctrl-C
 * @sig_num: the signal number
 * Return: void
 */

void sigintHandler(int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
	(void) sig_num;
}

/**
 * get_input - gets a line of input
 * @info: info struct
 * Return: num of bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len) /* we there is commands left in the chain buffer */
	{
		j = i;
		p = buf + i;
		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_DEFAULT;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
