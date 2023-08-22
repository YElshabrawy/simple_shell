#include "shell.h"
/**
* _strncpy - copies src to dst and returns it
* @dest: str 1 (destination)
* @src: str 2
* @n: cat val
* Return: ptr to dest
*/

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for ( ; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
* _strncat - concat 2 strings
* @dest: str 1 (destination)
* @src: str 2
* @n: cat val
* Return: ptr to dest
*/

char *_strncat(char *dest, char *src, int n)
{
	int len1 = 0, i = 0;

	while (dest[len1] != '\0')
		len1++;

	if (src[0])
	{
		while (src[i] != '\0' && i < n)
		{
			if (i == 0)
				dest[len1] = src[0];
			else
				dest[len1 + i] = src[i];
			i++;
		}
	}

	return (dest);
}

/**
* _strchr - returns the adress of the char in str
* @s: string
* @c: char to find
* Return: char address
*/

char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (!c)
		return (&s[i]);

	return (NULL);
}

/**
 * isDelim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int isDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _putfd - writes a character to given fd
 * @c: char
 * @fd: The file descriptor to write to
 *
 * Return: On success 1. On error, -1
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
