/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:48:00 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:48:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static char	*back_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_printf(STDERR_FILENO, "bash: cd: HOME not set\n");
		return (NULL);
	}
	return (ft_strdup(home));
}

static char	*get_target_path(int ac, char *path)
{
	if (ac == 1 || path == NULL || ft_strcmp(path, "~") == 0)
		return (back_home());
	return (ft_strdup(path));
}

int	ft_cd(int ac, char **av)
{
	char	*target_p;

	if (ac > 2)
	{
		ft_printf(STDERR_FILENO, "bash: cd: too many arguments\n");
		return (-1);
	}
	if (ac == 2 && ft_strcmp(av[1], ".") == 0)
		return (0);
	if (ac == 1)
		target_p = get_target_path(ac, NULL);
	else
		target_p = get_target_path(ac, av[1]);
	if (!target_p)
		return (-1);
	if (chdir(target_p) == -1)
	{
		ft_printf(2, "bash: cd: %s: %s\n", target_p, strerror(errno));
		free(target_p);
		return (-1);
	}
	free(target_p);
	return (0);
}
