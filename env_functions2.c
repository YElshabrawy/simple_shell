#include "shell.h"

/**
 * get_environ - returns the string array copy of env vars
 * @info: info struct
 * Return: array of string env vars
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _printenv - prints the current env vars
 * @info: info struct
 * Return: Always 0
 */

int _printenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * create_env_list - creates env linked list
 * @info: info struct
 * Return: Always 0
 */

int create_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
