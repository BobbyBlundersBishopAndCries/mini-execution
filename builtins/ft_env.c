#include "../exec.h"

static t_env	*create_env_node(char *valeur)
{
	t_env	*node;

	if (!valeur)
		return (NULL);
	node = malloc(sizeof(t_env));
	if(!node || !valeur)
		return (NULL);
	node->next = NULL;
	node->valeur = ft_strdup(valeur);
	if (!node->valeur)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

static void	free_env_list(t_env *head)
{
	t_env	*tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->valeur);
    	free(tmp);
    }
}

static void		addback_node(t_env **head, t_env *node)
{
	t_env	*curr;

	curr = *head;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
}

t_env	*create_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*node;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = create_env_node(env[i]);
		if (!node)
		{
			free_env_list(head);
			return (NULL);
		}
		addback_node(&head, node);
		i++;
	}
	return (head);
}

int	ft_env(char **env)
{
	t_env	*curr;
	t_env	*head;
;
	head = create_list(env);
	curr = head;
	if (!curr)
		return (1);
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "%s\n", curr->valeur);
		curr = curr->next;
	}
	free_env_list(head);
	return (0);
}
