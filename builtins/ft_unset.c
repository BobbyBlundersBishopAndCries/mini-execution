/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:08:44 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/01 03:33:21 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	free_node(t_env *node)
{
	free(node->whole);
	free(node->key);
	free(node->value);
	free(node);
}

static int del_arg(t_env **head, char *key)
{
	t_env	*curr;
	t_env	*previous;
	
	curr = *head;
	previous = NULL;
	if (head == NULL || *head == NULL || !key)
		return (0);
	while (curr)
	{
		if (ft_strcmp(key, curr->key) == 0)
		{
			if (previous)
				previous->next = curr->next;
			else
				*head = (*head)->next;
			free_node(curr);
			return (1);
		}
		previous = curr;
		curr = curr->next;
	}
	return (0);
}

static int is_valid_identifier(char *name)
{
	int	i;

	i = 1;
    if (!(ft_isalpha((unsigned char)name[0]) || name[0] == '_'))
        return (0);
    while (name[i])
    {
		if (!(ft_isalnum((unsigned char)name[i]) || name[i] == '_'))
			return 0;
		i++;
    }
    return 1;
}

int	ft_unset(int ac, char **av, char **env)
{
	int		i;
	t_env	*head; //needs to be static
	
	if (ac == 1)
		return (0);
	head = create_list(env);
	if (!head)
		return (1);
	i = 1;
	while (av[i])
	{
		if (!is_valid_identifier(av[i]))
		{
			ft_printf(2, "bash: unset `%s\': not a valid identifier\n", av[i]);
			return (1);
		}
		if (!del_arg(&head, av[i]))
			return (1);
		i++;
	}
	return (0);
}
