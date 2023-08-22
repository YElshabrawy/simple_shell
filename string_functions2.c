#include "shell.h"
/**
 * starts_with - checks if str starts with another str
 * @s1: string to search
 * @s2: substring to find
 *
 * Return: adress of the next char of main str or null
*/

char *starts_with(const char *s1, const char *s2)
{
	while (*s2)
		if (*s2++ != *s1++)
			return (NULL);
	return ((char *)s1);
}

/**
 * _puts - prints a str
 * @str: string to be printed (char[])
 * Return: void
*/

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - prints a character to stdout
 * @c: char
 *
 * Return: 1 on success, -1 on error
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(STDOUT_FILENO, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * **strtow - splits a string into words (repeated dilim are ignored)
 * @str: String
 * @d: the dilimeter string
 * Return: ptr to array of words
 */

char **strtow(char *str, char *d)
{
	int i, j, k, l, num_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!isDelim(str[i], d) && (isDelim(str[i + 1], d) || !str[i + 1]))
			num_of_words++;

	if (num_of_words == 0)
		return (NULL);
	s = malloc((1 + num_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_of_words; j++)
	{
		while (isDelim(str[i], d))
			i++;
		k = 0;
		while (!isDelim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: string
 * @d: the delimeter char
 * Return: ptr to array of words
 */

char **strtow2(char *str, char d)
{
	int i, j, k, m, num_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_of_words++;
	if (num_of_words == 0)
		return (NULL);
	s = malloc((1 + num_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_of_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
