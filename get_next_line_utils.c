/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/25 21:26:13 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_len(const char *s)
{
	size_t			i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*sub_str(char *s, size_t start, size_t len, int flag)
{
	char			*p;

	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (start < len)
	{
		p[start] = s[start];
		start++;
	}
	p[start] = '\0';
	if (flag)
		free(s);
	return (p);
}


int	find_nl(char *data, int *i)
{
	if (!data)
		return (0);
	*i = 0;
	while (data[*i])
	{
		if (data[*i] == '\n')
		{
			return (1);
		}
		(*i)++;
	}
	return (0);
}

char	*str_ncpy(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!n)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*p;
	size_t			len1;
	size_t			len2;

	len1 = get_len(s1);
	len2 = get_len(s2);
	if (!len1 && !len2)
		return (free(s1), free(s2), NULL);
	if (!len1)
		return (free(s1), sub_str(s2, 0, len2, 1));
	if (!len2)
		return (free(s2), sub_str(s1, 0, len1, 1));
	p = (char *)malloc(len1 + len2 + 1);
	if (!p)
		return (NULL);
	str_ncpy(p, s1, len1);
	str_ncpy(p + len1, s2, len2);
	free(s1);
	free(s2);
	return (p);
}
