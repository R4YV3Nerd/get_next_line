/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/24 00:53:38 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	str_len(const char *s) // we create a function that returns the length of a string

{
	size_t			index;

	if (!s)
		return (0);
	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*str_copy(char *s1, char *s2, size_t n) // we create a function that copies n bytes from s2 to s1
{
	size_t	index;

	if (!n)
	{
		free(s1);
		return (NULL);
	}
	index = 0;
	while (index < n)
	{
		s1[index] = s2[index];
		index++;
	}
	s1[index] = '\0';
	return (s1);
}

int	find_nl(char *data, int *index) // we create a function that finds a newline in the data
{
	if (!data)
		return (0);
	*index = 0;
	while (data[*index])
	{
		if (data[*index] == '\n')
		{
			return (1);
		}
		(*index)++;
	}
	return (0);
}

char	*str_sub(char *s, size_t start, size_t len, int flag) // performs two operations: it moves the string pointer to the new line character and returns the part from where the new line character was found to the end of the string.
{
	char			*ptr;

	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (start < len)
	{
		ptr[start] = s[start];
		start++;
	}
	ptr[start] = '\0';
	if (flag)
		free(s);
	return (ptr);
}

char	*str_join(char *s1, char *s2)
{
	char			*ptr;
	size_t			len1;
	size_t			len2;

	len1 = str_len(s1);
	len2 = str_len(s2);
	if (!len1 && !len2)
		return (free(s1), free(s2), NULL);
	if (!len1)
		return (free(s1), str_sub(s2, 0, len2, 1)); // we made it 1 to free the s2 and return the substring
	if (!len2)
		return (free(s2), str_sub(s1, 0, len1, 1)); // we made it 1 to free the s1 and return the substring
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	str_copy(ptr, s1, len1); // we copy the s1 to the ptr from 0 to len1 beacuse we want to copy the whole s1 to the ptr 
	str_copy(ptr + len1, s2, len2); // we copy the s2 to the ptr from len1 to len2 because we want to copy the whole s2 to the ptr
	free(s1);
	free(s2);
	return (ptr);
}
 