#include "shell.h"

/**
 * isInteractive - checks if interactive mode is on
 * @info: info addr
 * Return: 1 if interactive mode, 0 otherwise
*/
int isInteractive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= STDERR_FILENO);
}

/**
 * _isalpha - check if alpha char
 * @c: character to be checked
 * Description: check if alpha char
 * Return: 1 if c is alpha char, 0 otherwise
*/

int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
* _atoi - converts sting to int
* @s: string
* Return: int value of the string
*/
int _atoi(char *s)
{
	unsigned int result = 0;
	int sign = 1, i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
		}
		else if (result > 0)
			break;
		i++;
	}
	return (sign * result);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: number of total chars put
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

/**
 * print_d - function prints a decimal number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
