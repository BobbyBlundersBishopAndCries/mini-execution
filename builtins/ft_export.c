/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohabid <mohabid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/06/29 02:50:55 by mohabid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
				swap_strings(&(curr->whole), &(curr2->whole));
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

int	ft_export(char **env, char **av)
{
	t_env	*head;
	t_env	*curr;

	head = add_arguments(env, av);
	if (!head)
		return (0);
	curr = head;
	while (curr)
	{
		ft_printf(STDOUT_FILENO, "declare -x %s\n", curr->whole);
		curr = curr->next;
	}
	free_env_list(head);
	return (0);
}
