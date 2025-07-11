#include "../minishell.h"

static void	add_or_update_env(t_envlist *env, t_envlist *node);
static int	is_valid_identifier(const char *str);

void	ft_export(t_envlist *env, char **arg)
{
	t_envlist	*node;
	t_envlist	*next;

	if (!arg[1])
	{
		sort_envlist(env);
		print_export_format(env);
		return ;
	}
	node = envp_init(arg + 1);
	if (!node)
		return ;
	while (node)
	{
		next = node->next;
		if (!is_valid_identifier(node->key))
		{
			write(2, "export: `", 9);
			write(2, node->key, ft_strlen(node->key));
			write(2, "`: not a valid identifier\n", 26);
			g_last_exit = 1;
		}
		else
			add_or_update_env(env, node);
		node = next;
	}
	sort_envlist(env);
}

static t_envlist	*create_new_env_node(t_envlist *node)
{
	t_envlist	*new;

	new = malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
	new->key = ft_strdup(node->key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (node->value)
	{
		new->value = ft_strdup(node->value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

static void	add_or_update_env(t_envlist *env, t_envlist *node)
{
	t_envlist	*curr;
	t_envlist	*new;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, node->key) == 0)
		{
			if (curr->value)
				free(curr->value);
			if (node->value)
				curr->value = ft_strdup(node->value);
			else
				curr->value = NULL;
			curr->eq = node->eq;
			return ;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	new = create_new_env_node(node);
	if (!new)
		return ;
	curr->next = new;
}

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
