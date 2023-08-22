#include "shell.h"
/**
 * isExe - determines if a file is executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int isExe(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * split_path - splits a path from -> to
 * @pathStr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */

char *split_path(char *pathStr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathStr[i] != ':')
			buf[k++] = pathStr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * parse_path - finds a cmd in the PATH string
 * @info: the info struct
 * @pathStr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: path of cmd if found or NULL if not found
 */

char *parse_path(info_t *info, char *pathStr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (isExe(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathStr[i] || pathStr[i] == ':')
		{
			path = split_path(pathStr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isExe(info, path))
				return (path);
			if (!pathStr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
