#include "../minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	write_line(t_cmd *command)
{
	int	i;
	int	newline;

	if (!command->args[0])
		return ;
	if (ft_strcmp(command->args[0], "echo") != 0)
		return ;

	i = 1;
	newline = 1;
	while (command->args[i] && is_n_flag(command->args[i]))
	{
		newline = 0;
		i++;
	}
	while (command->args[i])
	{
		printf("%s", command->args[i]);
		if (command->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
