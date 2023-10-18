#include "main.h"

/**
 * non_interactive - fn
 *
 * Return: void
 */

void non_interactive(void)
{
	char **cur_cmd = NULL;
	int i, cmd_type = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&lines, &n, stdin) != -1)
		{
			remove_newline(lines);
			remove_comment(lines);
			cmds = tokenizer(lines, ";");
			for (i = 0; cmds[i] != NULL; i++)
			{
				cur_cmd = tokenizer(cmds[i], " ");
				if (cur_cmd[0] == NULL)
				{
					free(cur_cmd);
					break;
				}
				cmd_type = parse_cmd(cur_cmd[0]);
				initializer(cur_cmd, cmd_type);
				free(cur_cmd);
			}
			free(cmds);
		}
		free(lines);
		exit(status);
	}
}
