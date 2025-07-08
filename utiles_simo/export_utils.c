#include "../minishell.h"

void	swap_env_nodes(t_env *a, t_env *b)
{
	char *tmp_key;
	char *tmp_value;
	
	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	sort_list(t_env *head)
{
	t_env *curr;
	t_env *curr2;
	
	curr = head;
	while (curr)
	{
		curr2 = curr->next;
		while (curr2)
		{
			if (ft_strcmp(curr->key, curr2->key) > 0)
				swap_env_nodes(curr, curr2);
			curr2 = curr2->next;
		}
		curr = curr->next;
	}
}
