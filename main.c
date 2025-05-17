#include "minishell.h"

void	signal_handler(int sig);

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*command;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = read_multiline_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		else if (!(*input))
			continue ;
		add_history(input);
		command = token_separate(input);
		while (command)
		{
			if (command->cmd)
				printf("cmd :%s\n", command->cmd);
			if (command->args[0])
				printf("args[0] :%s\n", command->args[0]);
			if (command->args[1] && command->args[0])
				printf("args[1] :%s\n", command->args[1]);
			if (command->args[2]&& command->args[1] && command->args[0])
				printf("args[2] :%s\n", command->args[2]);
			if (command->args[3] && command->args[2]&& command->args[1] && command->args[0])
				printf("args[3] :%s\n", command->args[3]);
			if (command->infile)
				printf("infile :%s\n", command->infile);
			if (command->outfile)
				printf("outfile :%s\n", command->outfile);
			printf("%d\n", command->append);
			builtins(command, envp);
			command = command->next;
		}
		free(input);
	}
	return (0);
}

void	builtins(t_cmd *command, char *envp[])
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		write_line(command);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		print_location(command);
	else if (ft_strcmp(command->args[0], "env") == 0)
		environment(&env_list, envp);
}
void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
