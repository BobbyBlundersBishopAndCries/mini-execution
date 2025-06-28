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

static char *get_target_path(char *path)
{
	char *home;
    if (path == NULL || ft_strcmp(path, "~") == 0)
    {
		home = getenv("HOME");
        if (!home)
        {
            ft_printf(STDERR_FILENO, "cd: HOME not set\n");
            return (NULL);
        }
        else
			return (ft_strdup(home));
    }
	return (ft_strdup(path));
}

int ft_cd(char *path)
{
    char *target_path;

	if (path == NULL && ft_strcmp(path, ".") == 0)
		return (0);
	target_path = get_target_path(path);
	if (!target_path)
		return (-1);
	if (chdir(target_path) == -1)
	{
		ft_printf(STDERR_FILENO, "cd: %s: %s\n", target_path, strerror(errno));
		free(target_path);
		return (-1);
	}
	free(target_path);
	return (0);
}
