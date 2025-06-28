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

#include "../exec.h"

static int	arg_count(char **av)
{
	int	count;
	count = 0;
	while (NULL != av[count])
		count++;
	return (count);
}

int	ft_echo(char **av)
{
	int	i;
	int option;
	
	i = 1;
	option = 0;
	if (arg_count(av) == 1)
	{
		ft_printf(STDOUT_FILENO, "\n");
		return (0);
	}
	if (arg_count(av) > 1)
	{
		if (ft_strcmp(av[i], "-n") == 0)
		{
			option = 1;
			i++;
		}
		while(av[i] != NULL)
		{
			ft_printf(STDOUT_FILENO, "%s", av[i]);
			if (av[i + 1] != NULL)
				ft_printf(STDOUT_FILENO, " ");
			i++;
		}
	}
	if (option == 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
