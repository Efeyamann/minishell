#include "./../minishell.h"

static int	list_len(t_cmd	*list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	execute_builtin(t_cmd *cmd, t_envlist *env, int is_child)
{
	if (!cmd || !cmd->cmd)
		return ;
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		builtin_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		builtin_env(env);
	else if (ft_strcmp(cmd->cmd, "exit") == 0)
		builtin_exit(cmd, is_child);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		builtin_cd(cmd->args, env);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		builtin_unset(env, cmd->args);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		builtin_export(env, cmd->args);
}

static int	should_run_parent_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd || cmd->redirections)
		return (0);
	if (ft_strcmp(cmd->cmd, "cd") == 0
		|| ft_strcmp(cmd->cmd, "export") == 0
		|| ft_strcmp(cmd->cmd, "unset") == 0
		|| ft_strcmp(cmd->cmd, "exit") == 0)
		return (1);
	return (0);
}

void	ft_execute(t_envlist *env, t_cmd *cmd_list)
{
	if (!cmd_list || !cmd_list->cmd)
		return ;
	if (list_len(cmd_list) == 1 && is_builtin(cmd_list)
		&& should_run_parent_builtin(cmd_list))
	{
<<<<<<< HEAD
		execute_builtin(cmd_list, env, 0);
		return ;
=======
		if (!curr->next && is_builtin(curr) && curr == cmd_list)
		{
			handle_redirections_fd(curr);
			execute_builtin(curr, env);
		}
		else
		{
			if (curr->next)
				pipe(pipe_fd);
			pid = fork();
			if (pid == 0)
			{
				if (in_fd != 0)
				{
					dup2(in_fd, 0);
					close(in_fd);
				}
				if (curr->next)
				{
					close(pipe_fd[0]);
					dup2(pipe_fd[1], 1);
					close(pipe_fd[1]);
				}
				handle_redirections_fd(curr);
				if (is_builtin(curr))
				{
					handle_redirections_fd(curr);
					execute_builtin(curr, env);
					exit (0);
				}
				execute_external_command(curr, env);
				exit (127);
			}
			else
			{
				waitpid(pid, NULL, 0);
				if (in_fd != 0)
					close(in_fd);
				if (curr->next)
				{
					close(pipe_fd[1]);
					in_fd = pipe_fd[0];
				}
				g_last_exit = 1;
			}
		}
		curr = curr->next;
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876
	}
	execute_pipeline(cmd_list, env);
}
