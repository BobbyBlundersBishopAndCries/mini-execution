/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/07/06 11:20:10 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap_env_nodes(t_env *a, t_env *b)
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

static void	sort_list(t_env *head)
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

static void	add_export_arg(t_env **env, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_printf(STDERR_FILENO, "minishell: export: `%s`: not a valid identifier\n", arg);
		return ;
	}
	addback_node(env, arg);
	sort_list(*env);
}

static void	export_with_args(t_cmd *cmd)
{
	int i = 1;
	while (cmd->args[i])
	{
		add_export_arg(cmd->env, cmd->args[i]);
		i++;
	}
}

int	ft_export(t_cmd *cmd)
{
	t_env *curr;

	if (!cmd || !cmd->env || !(*cmd->env))
		return (1);
	if (arg_count(cmd->args) == 1)
	{
		sort_list(*cmd->env);
		curr = *cmd->env;
		while (curr)
		{
			printf("declare -x %s", curr->key);
			if (curr->value)
				printf("=\"%s\"", curr->value);
			printf("\n");
			curr = curr->next;
		}
	}
	else
		export_with_args(cmd);
	return (0);
}
