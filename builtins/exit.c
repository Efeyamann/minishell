#include "../minishell.h"

void	exit_program(t_cmd *commands)
{
	int	status;
	int	argc = 0;

	while (commands->args[argc])
		argc++;
	if (argc > 2)
	{
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 37);
		g_last_exit = 1;
		return ;
	}
	write(1, "exit\n", 5);
	if (argc == 1)
		status = 0;
	else if (!is_numeric(commands->args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, commands->args[1], ft_strlen(commands->args[1]));
		write(2, ": numeric argument required\n", 29);
		g_last_exit = 2;
		exit(2);
	}

	else
	{
		status = ft_atoi(commands->args[1]);
		g_last_exit = status;
	}
	exit(g_last_exit);
}
