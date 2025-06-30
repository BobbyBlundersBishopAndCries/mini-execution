/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:30:13 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/30 05:12:51 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

t_env	*create_env_node(char *arg)
{
	t_env	*node;

	if (!arg)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->whole = ft_strdup(arg);
	node->key = dup_key(arg);
	node->value = dup_value(arg);
	if (!node->whole)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

int	addback_node(t_env **head, char *av)
{
	t_env	*curr;
	t_env	*node;

	node = create_env_node(av);
	if (!node)
		return (1);
	curr = *head;
	if (*head == NULL)
	{
		*head = node;
		return (0);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return (0);
}

t_env	*create_list(char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		if (addback_node(&head, env[i]) == 1)
		{
			free_env_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}

int	ft_env(char **env)
{
	t_env	*curr;
	t_env	*head;

	head = create_list(env);
	curr = head;
	if (!curr)
		return (1);
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "%s\n", curr->whole);
		curr = curr->next;
	}
	free_env_list(head);
	return (0);
}
