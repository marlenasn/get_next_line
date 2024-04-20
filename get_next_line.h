/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:41:46 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/19 15:36:58 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct	s_Node
{
	struct s_Node	*next;
	char			*data;
};

size_t			ft_strlen(const char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
struct s_Node	*append(struct s_Node *head, char *str);
char			*get_next_line(int fd);
