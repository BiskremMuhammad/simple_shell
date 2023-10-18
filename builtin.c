#include "main.h"

/**
 *env - print en vars
 *@cmd: command
 *
 *Return: {void}
 */

void env(char **cmd __attribute__((unused)))
{
	int i;

	for (i = 0, envs[i] != NULL; i++)
	{
		print(envs[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * Quit - exit the shell
 * @cmd the command
 *
 * Return: void
 */

void quit(char **cmd)
{
	int c = 0, arg; 

	for (; cmd[c] != NULL; c++)
		;
	if (c == 1)
	{
		free(cmd);
		free(lines);
		free(cmds);
		exit(status);
	}
	else if (c == 2)
	{
		arg = _atoi(cmd[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(cmd[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(lines);
			free(cmd);
			free(cmds);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}

