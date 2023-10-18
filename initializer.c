#include "main.h"

/**
 * initializer - fn
 * @cur_cmd: p1
 * @cmd_type: p2
 *
 * Return: {void}
 */

void initializer(char **cur_cmd, int cmd_type)
{
	pid_t PID;

	if (cmd_type == EXT_CMD || cmd_type == PATH_CMD)
	{
		PID = fork();
		if (PID == 0)
			exec_cmd(cur_cmd, cmd_type);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		exec_cmd(cur_cmd, cmd_type);
}
