#include "shell.h"

/**
 * set_info - initializes info struct with the argv
 * @info: info addr
 * @av: arguments vector
 */

void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		/* count */
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		/* Dont forget the chains */
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * clear_info - clears info struct fields
 * @info: addr of info
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * free_info - frees info struct from memory
 * @info: struct address
 * @flush: 1 if freeing all fields, otherwise will not
 */

void free_info(info_t *info, int flush)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (flush)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
