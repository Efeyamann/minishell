#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_cmd t_cmd;


void		write_line(t_cmd *command);
void		print_location(void);
void		environment(t_envlist **list, char *envp[]);
void		exit_program(t_cmd *commands);
t_envlist	*find_node(t_envlist *list, char *key);
t_envlist	*export_create_env_node(char *env_string);
void		export_add_node(t_envlist **list, t_envlist *new_node);
void	export_new(t_cmd *command, t_envlist **env_list);
void	export_env(t_envlist **list, char *envp[], int a);
void	sort_env_and_print(t_envlist *env);


#endif