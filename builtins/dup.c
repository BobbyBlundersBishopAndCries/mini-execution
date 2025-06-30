#include "../exec.h"

char*	dup_key(char *arg)
{
	char	*key;
	int		i;
	
	i = 0;
	while (arg[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (arg[i] != '=')
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*dup_value(char *arg)
{
    int i = 0;
    int len;
    char *value;

    while (arg[i] && arg[i] != '=')
        i++;
    i++;
    len = ft_strlen(arg + i);
    value = malloc(len + 1);
    if (!value)
        return (NULL);
    for (int j = 0; j < len; j++)
        value[j] = arg[i + j];

    value[len] = '\0';
    return (value);
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->whole);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
