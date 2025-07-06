/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:50:09 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 14:25:04 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *line)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	if (!line[i] || !line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*new_line(char *buffer)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	str = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (buffer[i] != '\0')
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}
