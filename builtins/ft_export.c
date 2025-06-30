/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/06/30 05:19:53 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void swap_env_nodes(t_env *a, t_env *b)
{
    char *tmp_key;
    char *tmp_value;
    char *tmp_whole;

    tmp_key = a->key;
    a->key = b->key;
    b->key = tmp_key;

    tmp_value = a->value;
    a->value = b->value;
    b->value = tmp_value;

    tmp_whole = a->whole;
    a->whole = b->whole;
    b->whole = tmp_whole;
}

static void	sort_list(t_env *head)
{
	t_env	*curr;
	t_env	*curr2;

	curr = head;
	while (curr != NULL)
	{
		curr2 = curr->next;
		while (curr2 != NULL)
		{
			if (ft_strcmp(curr->whole, curr2->whole) > 0)
				swap_env_nodes(curr, curr2);
			curr2 = curr2->next;
		}
		curr = curr->next;
	}
}

static t_env	*add_arguments(char **env, char **av)
{
	int		i;
	t_env	*head;

	head = create_list(env);
	if (!head)
		return (NULL);
	i = 0;
	while (av[i] != NULL)
	{
		if (addback_node(&head, av[i]) == 1)
		{
			free_env_list(head);
			return (NULL);
		}
		sort_list(head);
		i++;
	}
	return (head);
}

int	ft_export(int ac, char **env, char **av)
{
	t_env	*head;// hadi atwli static bach n updatiha as long as prog khdam 
	t_env	*curr;

	head = add_arguments(env, av);
	curr = head;
	if (ac == 1)
	{
		while (curr)
		{
			printf("declare -x %s=", curr->key);
			printf("\"%s\"\n",curr->value);
			curr = curr->next;
		}
	}
	return (0);
}
