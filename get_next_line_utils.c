/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/31 00:29:31 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2) // allocates, concatenates and returns a new string with s1 and s2 
{
	char	*joined;
	int		i;
	int		j;

	if (s2[0] == '\0')
		return (0);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (0);
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
	if (s1)
		free(s1);
	return (joined);
} // if s2 was empty, we return 0 from the beginning to avoid allocating memory for nothing and to avoid memory leaks

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n') // while s exists and s[i] exists and s[i] is not a newline
		i++;
	if (s && s[i] == '\n') // if s exists and s[i] is a newline we increment i to include the newline in the length of the string
		i++;
	return (i);
}

int	ft_clean(char *str) // cleans the string by setting all characters to '\0' after the newline character and returns 1 if a newline character was found
{
	int	i;
	int	j;
	int	check;
// j and i are used to iterate through the string and check is used to check if a newline character was found in the string
	i = 0;
	j = 0;
	check = 0;
	while (str[i]) // this while will set all characters to '\0' after the newline character 
	{
		if (check) // if check is 1 we increment we enter the if, if check is 0 we dont enter the if
			str[j++] = str[i]; // we increment j only if we found a newline character because we want to keep the newline character in the string
		if (str[i] == '\n')
			check = 1;
		str[i++] = '\0'; // we set all characters to '\0' after the newline character
	}
	return (check);
}
