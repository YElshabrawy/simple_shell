#include "shell.h"

/**
 * _cd - change the dir
 * @info: info struct
 * Return: 0 on success, 1 on error
 */
int _cd(info_t *info)
{
	char *cwd, *dir, buffer[BUF_SIZE];
	int ret_val;

	cwd = getcwd(buffer, BUF_SIZE);
	if (!cwd)
		_puts("getcwd() failed: No such file or directory\n");
	if (!info->argv[1]) /* cd (with no extra args)*/
	{
		/* Navigate to HOME */
		dir = _getenv(info, "HOME=");
		if (!dir) /* If no home go to PWD*/
			ret_val = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			ret_val = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* cd - */
	{
		/* we chdir then print the new dir*/
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		ret_val = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else /* cd /var/www */
		ret_val = chdir(info->argv[1]);
	if (ret_val == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
		return (0);
	}
	/* Reset Env vars */
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, BUF_SIZE));
	return (0);
}

/**
 * _myexit - exits the shell
 * @info: info
 * Return: exit status
 */

int _myexit(info_t *info)
{
	int exit_condition;

	if (info->argv[1])
	{
		exit_condition = _erratoi(info->argv[1]);
		if (exit_condition == -1)
		{
			info->status = 2; /* Illegal num */
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exit_condition;
		return (-2);
	}
	info->err_num = -1; /* Default val */
	return (-2);
}

/**
 * _history - displays history list
 * @info: info struct
 * Return: void
 */

int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _alias - set alias for a givin string cmd (alias ga=git add)
 * @info: info struct
 * Return: Always 0
 */

int _alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
