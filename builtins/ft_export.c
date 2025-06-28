/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/06/27 22:10:02 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

static char	**sort_order(char **env)
{
	char	**sorted;
	int		i;
	int		j;
	
	i = 0;
	while (env[i])
		i++;
	sorted = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted)
		return (NULL);
	while (env[i + 1])
	{
		
	}
}
int	ft_export(char **env, char **args)
{
	int	i;

	i = 0;
	
}