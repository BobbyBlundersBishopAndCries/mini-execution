/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:08:44 by mohabid           #+#    #+#             */
/*   Updated: 2025/06/28 22:45:59 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	free_node(t_env *node)
{
	free(node->whole);
	free(node);
}

static t_env	*compare(char *arg, char **env)
{
	int	size;
	t_env	*head;
	t_env	*curr;
	
	if (env == NULL || *env == NULL || arg == NULL)
		return (NULL);
	head = create_list(env);
	curr = head;
	size = ft_strlen(arg);
	while (curr)
	{
		if (strncmp(arg, curr->whole, size) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_unset(char **av, char **env)
{
	t_env	*head;
	int		i;
	t_env	*curr;
	t_env	*tmp;
	
	head = create_list(env);
	curr = head;
	if (!head)
		return (0);
	i = 1;
	while (av[i])
	{
		if (compare(av[i], env) == head)
		{
			head = curr->next;
			tmp = curr;
			free_node(tmp);
		}
		else if (compare(av[i], env) == curr)
		{
			curr = curr
		}
	}
}
