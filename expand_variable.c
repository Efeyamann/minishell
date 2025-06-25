#include "minishell.h"

static int	is_valid_var_start(char c);
static char	*find_var_name(char *str);
static char	*strjoin_char(char *s, char c);
static char	*find_value(char *str, t_envlist *env);

char	*expand_variable(char *str, t_envlist *env)
{
	int		i;
	char	*var_name;
	char	*value;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				//In here
			}
			else if (is_valid_var_start(str[i + 1]))
			{
				var_name = find_var_name(&str[i + 1]);
				value = find_value(var_name, env);
				free(var_name);
				i += ft_strlen(var_name) + 1;
			}
			else
			{
				result = strjoin_char(result, '$');
				i++;
			}
		}
		else
		{
			result = strjoin_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

static char	*find_value(char *str, t_envlist *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static char	*find_var_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] != ' ' && (fisalnum(str[i] || str[i] == '_')))
		i++;
	return (ft_substr(str, 0, i));
}

static int	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static char	*strjoin_char(char *s, char c)
{
	size_t	len;
	char	*new_str;

	if (!s)
	{
		new_str = (char *)malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = strlen(s);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (NULL);
	memcpy(new_str, s, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(s);
	return (new_str);
}
