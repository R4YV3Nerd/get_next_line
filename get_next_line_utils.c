/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/04 09:18:19 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (s2[0] == '\0')
		return (0);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)); // allocates enough memory for s1 and s2
	if (!joined)
		return (0);
	i = 0;
	while (s1 && s1[i]) // copies s1 into joined until the end of s1
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n') // copies s2 into joined until the end of s2 or a newline
		joined[i++] = s2[j++];
	if (s2[j] == '\n') // if a newline is found, it is copied into joined and the rest of s2 is ignored (the rest of s2 is the next line) , the new line is returned along with the rest of s2
		joined[i++] = '\n';
	joined[i] = '\0';
	free(s1);
	return (joined);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

int	ft_clean(char *str) // this function is used to clean the buffer after a newline is found in the buffer
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (str[i])
	{
		if (check)
			str[j++] = str[i];
		if (str[i] == '\n')
			check = 1;
		str[i++] = '\0';
	}
	return (check);
}
