/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:08:44 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/30 07:21:25 by med              ###   ########.fr       */
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

static void	del_arg(t_env **head, t_env *arg)
{
	t_env	*curr;
	t_env	*previous;
	
	curr = (*head)->next;
	previous = *head;
	if (head == NULL || *head == NULL)
		return ;
	if (*head == arg)
	{
		*head = (*head)->next;
		free_node(previous);
		return ;
	}
	while (curr)
	{
		if (arg == curr)
		{
			previous->next = curr->next;
			free_node(curr);
			return ;
		}
		previous = curr;
		curr = curr->next;
	}
}
static t_env	*arg_to_unset(char *arg, char **env)
{
	t_env	*head;
	t_env	*curr;
	
	if (env == NULL || *env == NULL || arg == NULL)
		return (NULL);
	head = create_list(env);
	curr = head;
	while (curr)
	{
		if (strcmp(arg, curr->key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_unset(int ac, char **av, char **env)
{
	if (ac == 1)
		return (0);
	
}
