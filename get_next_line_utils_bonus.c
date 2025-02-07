/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 08:02:39 by maitoumg          #+#    #+#             */
/*   Updated: 2025/02/06 16:44:17 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (s2[0] == '\0')
		return (free(s1), s1 = NULL, NULL);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
		joined[i++] = s2[j++];
	if (s2[j] == '\n')
		joined[i++] = '\n';
	joined[i] = '\0';
	return (free(s1), s1 = NULL, joined);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (check)
			str[j++] = str[i];
		if (str[i] == '\n')
			check = 1;
		str[i++] = '\0';
	}
	str[j] = '\0';
	return (check);
}
