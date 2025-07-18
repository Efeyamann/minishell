#include "../minishell.h"

<<<<<<< HEAD
static void	sort_envlist(t_envlist *list);
static void	print_export_format(t_envlist *list);
=======
static void	add_or_update_env(t_envlist *env, t_envlist *node);
static int	is_valid_identifier(const char *str);
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876

void	builtin_export(t_envlist *env, char **arg)
{
	int	i;
	int	has_error;

	has_error = 0;
	i = 1;
	if (!arg[1])
	{
		sort_envlist(env);
		print_export_format(env);
		g_last_exit = 0;
		return ;
	}
	while (arg[i])
	{
<<<<<<< HEAD
		if (handle_single_export_arg(env, arg[i]))
			has_error = 1;
		i++;
=======
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
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876
	}
	if (has_error)
		g_last_exit = 1;
	else
		g_last_exit = 0;
	sort_envlist(env);
}

static void	print_export_format(t_envlist *list)
{
	while (list)
	{
		printf("declare -x %s", list->key);
		if (list->value)
			printf("=\"%s\"", list->value);
		printf("\n");
		list = list->next;
	}
}

static void	swap_env_content(t_envlist *a, t_envlist *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

static void	sort_envlist(t_envlist *list)
{
	t_envlist	*curr;
	t_envlist	*end;
	int			sorted;

	end = NULL;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = list;
		while (curr && curr->next != end)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
			{
				swap_env_content(curr, curr->next);
				sorted = 0;
			}
			curr = curr->next;
		}
		end = curr;
	}
}
<<<<<<< HEAD
=======

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
>>>>>>> c6c9aae7735f0c9e87735e08ea11841bd18a0876
