#include "../../include/builtins.h"
int	cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->count > 2)
	{
		write(2, "Error: Too Many Args\n", 21);
		return (1);
	}
	if (cmd->count == 1)
	{
		path = getenv("HOME");
		if (!path)
		{
			write(2, "Error: HOME not set\n", 21);
			return (1);
		}
	}
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		write(2, "Error: No Such File or Directory\n", 33);
		return (1);
	}
	// getcwd(path, 1024);
	// printf("%s\n", path);
	return (0);
}
