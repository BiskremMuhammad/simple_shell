#include "main.h"

/**
 * _getenv - get env vars with a name
 * @var: var name
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *var)
{
	char **vars;
	char *ptr;
	char *tmp;

	for (vars = envs; *vars != NULL; vars++)
	{
		for (ptr = *vars, tmp = var;
		     *ptr == *tmp; ptr++, tmp++)
		{
			if (*ptr == '=')
				break;
		}
		if ((*ptr == '=') && (*tmp == '\0'))
			return (ptr + 1);
	}
	return (NULL);
}

/**
 *print - fn
 *@str: the string
 *@stream: stream to print
 *
 *Return: {void}
 */
void print(char *str, int stream)
{
	int i = 0;

	for (; str[i] != '\0'; i++)
		write(stream, &str[i], 1);
}

/**
 *_strlen - gets string length
 *@str: the string
 *
 * Return: {int} string length
 */

int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (len);
	for (; str[len] != '\0'; len++)
		;
	return (len);
}

/**
 * _atoi - fn
 * @s: the string
 *
 * Return: {int}
 */
int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 *_strcpy - fn
 *@src: src
 *@dest: destination
 *
 * Return: {void}
 */

void _strcpy(char *src, char *dest)
{
	int i = 0;

	for (; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}

/**
 *_strcmp - fn
 *@a: s1
 *@b: s2
 *
 * Return: {int} result
 */

int _strcmp(char *a, char *b)
{
	int i = 0;

	while (a[i] != '\0')
	{
		if (a[i] != b[i])
			break;
		i++;
	}
	return (a[i] - b[i]);
}

/**
 *_strcat - fn to concat strings
 *@dest: s1
 *@src:  s2
 *
 * Return: {char}
 */

char *_strcat(char *dest, char *src)
{
	char *result =  NULL;
	int dest_len = _strlen(dest);
	int src_len = _strlen(src);

	result = malloc(sizeof(*result) * (dest_len + src_len + 1));
	_strcpy(dest, result);
	_strcpy(src, result + dest_len);
	result[dest_len + src_len] = '\0';
	return (result);
}

/**
 *_strspn - fn
 *@dest: s1
 *@src:  s2
 *
 *Return: number of bytes in the initial segment of 5 which are part of accept
 */

int _strspn(char *a, char *b)
{
	int i = 0;
	int res = 0;

	while (a[i] != '\0')
	{
		if (_strchr(b, a[i]) == NULL)
			break;
		res++;
		i++;
	}
	return (res);
}

/**
 *_strcspn - fn
 *@a: s1
 *@b: s2
 *
 *Return: {int}
 */

int _strcspn(char *a, char *b)
{
	int len = 0, i;

	for (i = 0; a[i] != '\0'; i++)
	{
		if (_strchr(b, a[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *_strchr - fn
 *@s: string
 *@c: char
 *
 *Return: {char}
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

/**
 * tokenizer - fn
 *@str: input
 *@delim: delimiter
 *
 *Return: {char} tokens of the input
 */

char **tokenizer(char *str, char *delim)
{
	int dlm_nums = 0;
	char **av = NULL;
	char *t = NULL;
	char *ptr = NULL;

	t = _strtok_r(str, delim, &ptr);

	while (t != NULL)
	{
		av = _realloc(av, sizeof(*av) * dlm_nums, sizeof(*av) * (dlm_nums + 1));
		av[dlm_nums] = t;
		t = _strtok_r(NULL, delim, &ptr);
		dlm_nums++;
	}

	av = _realloc(av, sizeof(*av) * dlm_nums, sizeof(*av) * (dlm_nums + 1));
	av[dlm_nums] = NULL;

	return (av);
}

/**
 *_strtok_r - fn
 *@str: the string
 *@delim: string delimiter
 *@ptr: string pointer
 *
 *Return: {char}
 */
char *_strtok_r(char *str, char *delim, char **ptr)
{
	char *end;

	if (str == NULL)
		str = *ptr;

	if (*str == '\0')
	{
		*ptr = str;
		return (NULL);
	}

	str += _strspn(str, delim);
	if (*str == '\0')
	{
		*ptr = str;
		return (NULL);
	}

	end = str + _strcspn(str, delim);
	if (*end == '\0')
	{
		*ptr = end;
		return (str);
	}

	*end = '\0';
	*ptr = end + 1;
	return (str);
}

/**
 * _realloc - fn
 * @ptr: pointer
 * @old: size of pointer
 * @new_size: pointer new size
 *
 * Return: {void}
 */
void *_realloc(void *ptr, unsigned int old, unsigned int new_size)
{
	void *tmp;
	unsigned int i;

	if (ptr == NULL)
	{
		tmp = malloc(new_size);
		return (tmp);
	}
	else if (new_size == old)
		return (ptr);
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		tmp = malloc(new_size);
		if (tmp != NULL)
		{
			for (i = 0; i < min(old, new_size); i++)
				*((char *)tmp + i) = *((char *)ptr + i);
			free(ptr);
			return (tmp);
		}
		else
			return (NULL);
	}
}

/**
 * ctrl_c_handler - CTRL-C handler
 * @signal: signal number
 *
 * Return: void
 */
void ctrl_c_handler(int signal)
{
	if (signal == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 *remove_newline - fn
 *@str: string
 *
 *Return: {void}
 */

void remove_newline(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	str[i] = '\0';
}

/**
 * remove_comment - fn
 * @input: input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}

/**
 * check_path - fn
 * @cmd: the command
 *
 * Return: {char} the path
 */
char *check_path(char *cmd)
{
	char **path_arr = NULL;
	char *tmp, *tmp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_arr = tokenizer(path_cpy, ":");
	for (i = 0; path_arr[i] != NULL; i++)
	{
		tmp2 = _strcat(path_arr[i], "/");
		tmp = _strcat(tmp2, cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp2);
			free(path_arr);
			free(path_cpy);
			return (tmp);
		}
		free(tmp);
		free(tmp2);
	}
	free(path_cpy);
	free(path_arr);
	return (NULL);
}

/**
 * get_func - fn
 * @cmd: string to check against the mapped
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *cmd))(char **)
{
	int i;
	func_map mapped[] = {
		{"env", env}, {"exit", quit}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(cmd, mapped[i].cmd) == 0)
			return (mapped[i].func);
	}
	return (NULL);
}

/** parse_cmd - parse the commnad
 * @cmd: the command
 *
 * Return: {int} command type
 */

int parse_cmd(char *cmd)
{
	int i;
	char *internal_cmd[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] == '/')
			return (EXT_CMD);
	}
	for (i = 0; internal_cmd[i] != NULL; i++)
	{
		if (_strcmp(cmd, internal_cmd[i]) == 0)
			return (INT_CMD);
	}
	/* @check_path - checks if a cmd is found in the PATH */
	path = check_path(cmd);
	if (path != NULL)
	{
		free(path);
		return (PATH_CMD);
	}

	return (INVALID_CMD);
}

/**
 * exec_cmd - executes a command
 * @cmd: the command
 * @cmd_type: command type
 *
 * Return: {void}
 */
void exec_cmd(char **cmd, int cmd_type)
{
	void (*func)(char **commands);

	if (cmd_type == EXT_CMD)
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_type == PATH_CMD)
	{
		if (execve(check_path(cmd[0]), cmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_type == INT_CMD)
	{
		func = get_func(cmd[0]);
		func(cmd);
	}
	if (cmd_type == INVALID_CMD)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(cmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}
