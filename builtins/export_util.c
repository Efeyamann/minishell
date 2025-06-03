#include "../minishell.h"

void	print_export_format(t_envlist *list)
{
	while (list)
	{
		printf("declare -x %s", list->key);
		if (list->value)
		{
			printf("=\"%s\"", list->value);
		}
		printf("\n");
		list = list->next;
	}
}
