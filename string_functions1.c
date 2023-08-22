#include "shell.h"
/**
 * _strlen - returns str length
 * @s: string (char[])
 * Return: length of string
*/

int _strlen(char *s)
{
	int c = 0;

	while (s[c] != '\0')
		c++;
	return (c);
}

/**
* _strcmp - compares 2 str
* @s1: string 1
* @s2: string 2
* Return: 0 if equal, otherwise difference between first
* different characters
*/

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
* _strcat - concat 2 strings
* @dest: str 1 (destination)
* @src: str 2
* Return: ptr to dest
*/

char *_strcat(char *dest, char *src)
{
	int len1 = 0, i = 1;

	while (dest[len1] != '\0')
		len1++;

	if (src[0])
	{
		dest[len1] = src[0];

		while (src[i] != '\0')
		{
			dest[len1 + i] = src[i];
			i++;
		}
	}

	return (dest);

}

/**
* _strcpy - copies the string pointed to by src
* @dest: destination string
* @src: source string
* Return: the dest string
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strdup - duplicates a string
* @s: string
* Return: ptr to the duplicate
*/
char *_strdup(const char *s)
{
	int len = 0;
	char *output;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;

	output = malloc(len + 1);
	if (!output)
		return (NULL);

	for (len++; len--;)
		output[len] = *--s;
	return (output);

}
