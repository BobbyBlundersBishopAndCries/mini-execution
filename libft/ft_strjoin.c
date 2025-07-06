/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med <med@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:42:02 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/06 15:05:59 by med              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}

/*
int main()
{
	const char *s1 = "Hello ";
	const char *s2 = "wol0d";
	char *joined = ft_strjoin(s1,s2);
	if(joined)
	{
		printf("The concatenated strings are %s\n",joined);
		free(joined);
	}
	else
		printf("Memory allocation failure.\n");
	return 0;
}*/
