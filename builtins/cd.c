#include "../minishell.h"

static int	update_pwd_vars(char *oldpwd);
static char	*resolve_cd_target(char **args);

int	builtin_cd(char **args)
{
	char	cwd[1024];
	char	*oldpwd;
	char	*target;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (1);
	target = resolve_cd_target(args);
	if (!target || chdir(target) != 0)
	{
		if (target)
			perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	return (update_pwd_vars(oldpwd));
}

static int	update_pwd_vars(char *oldpwd)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("minishell: cd: getcwd after chdir");
		free(oldpwd);
		return (1);
	}
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", cwd, 1);
	free(oldpwd);
	return (0);
}

static char	*resolve_cd_target(char **args)
{
	char	*target;

	if (!args[1] || ft_strcmp(args[1], "") == 0 || ft_strcmp(args[1], "~") == 0)
	{
		target = getenv("HOME");
		if (!target)
			write(2, "minishell: cd: HOME not set\n", 29);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = getenv("OLDPWD");
		if (target)
			printf("%s\n", target);
		else
			write(2, "minishell: cd: OLDPWD not set\n", 30);
	}
	else
		target = args[1];
	return (target);
}
