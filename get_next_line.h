/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 03:45:26 by maitoumg          #+#    #+#             */
/*   Updated: 2025/01/23 23:49:46 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*str_copy(char *s1, char *s2, size_t n);
int		find_nl(char *data, int *i);
char	*get_next_line(int fd);
size_t	str_len(const char *s);
char	*str_sub(char *s, size_t start, size_t len, int flag);
char	*str_join(char *s1, char *s2);
#endif
