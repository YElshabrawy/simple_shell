#include "shell.h"
/**
* _memset - fills the first n bytes of the memory area
* pointed to by s with the constant byte b
* @s: start adr
* @b: byte per adr
* @n: num of elements to fill
* Return: pointer to the starting position
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		*(s + i) = b;

	return (s);
}

/**
* _realloc - reallocates a memory block
* @ptr: pointer to the prev block
* @old_size: size of the allocated space for ptr
* @new_size: new size
* Return: ptr to new block
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *res;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		res = malloc(new_size);
		if (!res)
			return (NULL);
		return (res);
	}

	res = malloc(new_size);
	if (!res)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		res[i] = ((char *)ptr)[i];

	free(ptr);
	return (res);
}

/**
 * ffree - frees an array of strings
 * @pstr: arr of strings
 * Return: void
 */

void ffree(char **pstr)
{
	char **a = pstr;

	if (!pstr)
		return;
	while (*pstr)
		free(*pstr++);
	free(a);
}

/**
 * bfree - free a ptr and NULLs the address
 * @addr: address of the ptr to be free
 * Return: 1 on success, else 0
 */

int bfree(void **addr)
{
	if (addr && *addr)
	{
		free(*addr);
		*addr = NULL;
		return (1);
	}
	return (0);
}
