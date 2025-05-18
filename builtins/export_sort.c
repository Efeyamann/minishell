#include "../minishell.h"

void	sort_env_and_print(t_envlist *env)
{
	t_envlist	**array;
	t_envlist	*tmp;
	t_envlist	*swap;
	int			count;
	int			i;
	int			j;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(t_envlist *) * count);
	if (!array)
		return ;
	i = 0;
	tmp = env;
	while (i < count)
	{
		array[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				swap = array[j];
				array[j] = array[j + 1];
				array[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[i]->key, 1);
		if (array[i]->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(array[i]->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
	free(array);
}
