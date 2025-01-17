/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maitoumg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:25:10 by ocartier          #+#    #+#             */
/*   Updated: 2025/01/11 15:50:59 by maitoumg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>

typedef struct s_prev_list
{
	char				*prev;
	int					fd;
	struct s_prev_list	*next;
}	t_prev_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
long	charchr(const char *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	shiftstr(char **str, size_t start);
#endif
