#include "main.h"

char *shell_name = NULL;
char **envs = NULL;
char *lines = NULL;
char **cmds = NULL;
int status = 0;

/**
 * main - MAIN
 * @argc: args count
 * @argv: arg values
 * 
 * Return: {int}
 */


int main(int argc __attribute__((unused)), char **argv)
{
	char **crr_cmd = NULL;
	int i, cmd_type = 0;
	size_t n = 0;

	signal(SIGINT, ctrl_c_handler);
	shell_name = argv[0];
	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&lines, &n, stdin) == -1)
		{
			free(lines);
			exit(status);
		}
			remove_newline(lines);
			remove_comment(lines);
			cmds = tokenizer(lines, ";");

		for (i = 0; cmds[i] != NULL; i++)
		{
			crr_cmd = tokenizer(cmds[i], " ");
			if (crr_cmd[0] == NULL)
			{
				free(crr_cmd);
				break;
			}
			cmd_type = parse_cmd(crr_cmd[0]);

			/* initializer -   */
			initializer(crr_cmd, cmd_type);
			free(crr_cmd);
		}
		free(cmds);
	}
	free(lines);

	return (status);
}

