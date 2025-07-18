#include "minishell.h"

<<<<<<< HEAD
int	g_last_exit = 0;
=======
int g_last_exit = 0;

void			signal_handler(int sig);
static void		parse_execute(char *input, t_envlist *env);
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876

void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char		*input;
	t_envlist	*env;

	g_last_exit = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	env = envp_init(environ);
	while (1)
	{
		input = read_multiline_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		else if (!(*input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		parse_execute(input, env);
		free(input);
	}
<<<<<<< HEAD
	return (g_last_exit);
=======
	return (0);
}

void	signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	parse_execute(char *input, t_envlist *env)
{
	t_token		*tokens;
	t_cmd		*commands;
	int			i;
	char		*expanded;

	i = 0;
	tokens = tokenize(input);
	commands = parse_commands(tokens);
	while (commands && commands->args && commands->args[i])
	{
		if (ft_strchr(commands->args[i], '$'))
		{
			expanded = expand_variable(commands->args[i], env);
			free(commands->args[i]);
			commands->args[i] = expanded;
		}
		i++;
	}
	ft_execute(env, commands);
	free_tokens(tokens);
	free_commands(commands);
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876
}
