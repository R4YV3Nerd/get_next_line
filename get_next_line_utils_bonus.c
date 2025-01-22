/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:50:24 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/26 12:55:27 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_str_len(const char *s)
{ 
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

static size_t	copy_string_safe(char *dst, const char *src, size_t size)
{
	size_t	index;

	if (size == 0)
		return (get_str_len(src));
	index = 0;
	while (src[index] && index < (size - 1))
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (get_str_len(src));
}
long	find_character(const char *s, char c)
{
	long	index;

	index = 0;
	while (s[index])
	{
		if (s[index] == (unsigned char)c)
			return (index);
		index++;
	}
	if (s[index] == (unsigned char)c)
		return (index);
	return (-1);
}
char	*concat_strings(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*concated_string;

	if (!s1 || !s2)
		return (NULL);
	s1_len = get_str_len(s1);
	s2_len = get_str_len(s2);
	concated_string = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!concated_string)
		return (NULL);
	copy_string_safe(concated_string, s1, s1_len + 1);
	copy_string_safe((concated_string + s1_len), s2, s2_len + 1);
	free(s1);
	return (concated_string);
}
char	*extract_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring_result;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (get_str_len(s) < start)
	{
		substring_result = malloc(sizeof(char));
		substring_result[0] = 0;
		if (!substring_result)
			return (NULL);
	}
	else
	{
		new_len = get_str_len(s + start);
		if (!(new_len < len))
			new_len = len;
		substring_result = (char *)malloc((new_len + 1) * sizeof(char));
		if (!substring_result)
			return (NULL);
		substring_result[new_len] = 0;
		while (new_len-- > 0)
			substring_result[new_len] = s[start + new_len];
	}
	return (substring_result);
}
