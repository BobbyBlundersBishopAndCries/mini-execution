/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/07/08 15:24:42 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*find_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static void	update_env_value(t_env *node, char *value)
{
	if (!node)
		return ;
	free(node->value);
	node->value = ft_strdup(value);
}

static void	handle_new_export(t_env **env, char *arg)
{
	addback_node(env, arg);
	sort_list(*env);
}

static void	export_argument(t_env **env, char *arg)
{
	char	*eq;
	char	*key;
	char	*val;
	t_env	*existing;

	if (!is_valid_identifier(arg))
		return ((void)ft_printf(2, "minishell: export: `%s`: not a valid identifier\n", arg));
	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		existing = find_env_node(*env, arg);
		if (!existing)
			handle_new_export(env, arg);
		return ;
	}
	key = ft_substr(arg, 0, eq - arg);
	val = ft_strdup(eq + 1);
	existing = find_env_node(*env, key);
	if (existing)
		update_env_value(existing, val);
	else
		handle_new_export(env, arg);
	free(key);
	free(val);
}

static void	export_with_args(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		export_argument(cmd->env, cmd->args[i]);
		i++;
	}
}

int	ft_export(t_cmd *cmd)
{
	t_env	*curr;

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
