/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/27 17:47:15 by maitoumg         ###   ########.fr       */
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

char	*sub_str(char *s, size_t start, size_t len, int flag) // we use substr to get the line from the buffer and then we free the buffer
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

int	find_nl(char *data, int *i)
{
	if (!data)
		return (0);
	*i = 0; // this is not dereferencing a null pointer because we are passing the address of i and not the value of i
	while (data[*i])
	{
		if (data[*i] == '\n')
		{
			return (1); // means yes we found a new line
		}
		(*i)++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*p;
	size_t			len1;
	size_t			len2;

	len1 = get_len(s1);
	len2 = get_len(s2);
	if (!len1 && !len2) // if both are empty we return NULL and free the memory of s1 and s2
		return (free(s1), free(s2), NULL);
	if (!len1) // if s1 is empty we return s2 which is the line and free s1 memory
		return (free(s1), sub_str(s2, 0, len2, 1));
	if (!len2) // if s2 is empty we return s1 and free s2 memory
		return (free(s2), sub_str(s1, 0, len1, 1));
	p = (char *)malloc(len1 + len2 + 1); // we allocate memory for both strings and the null terminator 
	if (!p)
		return (NULL);
	str_ncpy(p, s1, len1);
	str_ncpy(p + len1, s2, len2);
	free(s1);
	free(s2);
	return (p);
}
