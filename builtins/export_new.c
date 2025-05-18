#include "../minishell.h"

void	print_error(t_cmd *command, int i);
void	add_to_list(char *arg, t_envlist **env_list);
void	split_key_value(char *arg, char **key, char **value);
t_envlist *create_export_node(char *key, char *value);

void	export_new(t_cmd *command, t_envlist **env_list)
{
	int	i;
	int	j;
	int	valid;

	i = 1;
	while (command->args[i])
	{
		valid = 1;
		if (command->args[i][0] != '_' && ft_isalpha(command->args[i][0]) == 0)
		{
			print_error(command, i);
			i++;
			continue ;
		}
		j = 1;
		while (command->args[i][j] && command->args[i][j] != '=')
		{
			if (command->args[i][j] != '_' && ft_isalnum(command->args[i][j]) == 0)
			{
				print_error(command, i);
				valid = 0;
				break ;
			}
			j++;
		}
		if (valid == 1)
			add_to_list(command->args[i], env_list);
		i++;
	}
}

void	add_to_list(char *arg, t_envlist **env_list)
{
	char		*key;
	char		*value;
	t_envlist	*node;
	t_envlist	*new_node;

	split_key_value(arg, &key, &value);
	if (!key)
		return ;
	node = find_node(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
	{
		new_node = create_export_node(key, value);
		if (!new_node)
		{
			free(key);
			free(value);
			return ;
		}
		export_add_node(env_list, new_node);
	}
}

t_envlist *create_export_node(char *key, char *value)
{
	t_envlist *node;

	node = malloc(sizeof(t_envlist));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	split_key_value(char *arg, char **key, char **value)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		*key = strndup(arg, equal_pos - arg);
		*value = ft_strdup(equal_pos + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

void	print_error(t_cmd *command, int i)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(command->args[i], 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
