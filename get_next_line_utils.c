/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 02:04:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/16 17:19:34 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_string_length(const char *s)
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
		return (get_string_length(src));
	index = 0;
	while (src[index] && index < (size - 1))
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (get_string_length(src));
}

long	find_char(const char *s, char c)
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
	size_t	first_string_length;
	size_t	second_string_length;
	char	*concatenated_string;

	if (!s1 || !s2)
		return (NULL);
	first_string_length = get_string_length(s1);
	second_string_length = get_string_length(s2);
	concatenated_string = (char *)malloc((first_string_length + second_string_length + 1) * sizeof(char));
	if (!concatenated_string)
		return (NULL);
	copy_string_safe(concatenated_string, s1, first_string_length + 1);
	copy_string_safe((concatenated_string + first_string_length), s2, second_string_length + 1);
	free(s1);
	return (concatenated_string);
}

char	*extract_substring(char const *s, unsigned int start, size_t len)
{
	char	*substring_result;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (get_string_length(s) < start)
	{
		substring_result = malloc(sizeof(char));
		substring_result[0] = 0;
		if (!substring_result)
			return (NULL);
	}
	else
	{
		new_len = get_string_length(s + start);
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
