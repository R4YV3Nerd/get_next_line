/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:04:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/07 02:04:29 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	string_length(const char *s)
{
	size_t	cur;

	cur = 0;
	while (s[cur])
		cur++;
	return (cur);
}

static size_t	strlcpy_custom(char *dst, const char *src, size_t size)
{
	size_t	cur;

	if (size == 0)
		return (string_length(src));
	cur = 0;
	while (src[cur] && cur < (size - 1))
	{
		dst[cur] = src[cur];
		cur++;
	}
	dst[cur] = 0;
	return (string_length(src));
}

long	find_char(const char *s, char c)
{
	long	cur;

	cur = 0;
	while (s[cur])
	{
		if (s[cur] == (unsigned char)c)
			return (cur);
		cur++;
	}
	if (s[cur] == (unsigned char)c)
		return (cur);
	return (-1);
}

char	*string_join(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = string_length(s1);
	s2_len = string_length(s2);
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	strlcpy_custom(join, s1, s1_len + 1);
	strlcpy_custom((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

char	*substring(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (string_length(s) < start)
	{
		sub = malloc(sizeof(char));
		sub[0] = 0;
		if (!sub)
			return (NULL);
	}
	else
	{
		new_len = string_length(s + start);
		if (!(new_len < len))
			new_len = len;
		sub = (char *)malloc((new_len + 1) * sizeof(char));
		if (!sub)
			return (NULL);
		sub[new_len] = 0;
		while (new_len-- > 0)
			sub[new_len] = s[start + new_len];
	}
	return (sub);
}
