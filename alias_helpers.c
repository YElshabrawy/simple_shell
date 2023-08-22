#include "shell.h"
/**
 * unset_alias - unsets alias
 * @info: info struct
 * @name: the string alias name
 * Return: 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *name)
{
	char *p, c;
	int ret;

	p = _strchr(name, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, name, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias
 * @info: info struct
 * @name: the string alias
 * Return: 0 on success, 1 on error
 */

int set_alias(info_t *info, char *name)
{
	char *p;

	p = _strchr(name, '=');
	if (!p) /* alias garbage*/
		return (1);
	if (!*++p) /* alias name= */
		return (unset_alias(info, name));

	unset_alias(info, name);
	return (add_node_end(&(info->alias), name, 0) == NULL); /* alias name=val */
}

/**
 * print_alias - prints an alias value
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
