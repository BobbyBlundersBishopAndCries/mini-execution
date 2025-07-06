/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:28:20 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:28:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check(char *str)
{
	int i;

	i = 0;
	if(!str[i])
		return 0;
	if(str[i] == '-')
		i++;
	while(str[i] == 'n')
		i++;
	if(!str[i])
		return 1;
	return 0;
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (arg_count(cmd->args) == 1)
		return (ft_printf(STDOUT_FILENO, "\n"));
	if (arg_count(cmd->args) > 1)
	{
		while (ft_strcmp(cmd->args[i], "-n") == 0 || check(cmd->args[i]))
		{
			option = 1;
			i++;
		}
		while (cmd->args[i] != NULL)
		{
			ft_printf(STDOUT_FILENO, "%s", cmd->args[i]);
			if (cmd->args[i + 1] != NULL)
				ft_printf(STDOUT_FILENO, " ");
			i++;
		}
	}
	if (option == 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
