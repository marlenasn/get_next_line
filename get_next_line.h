/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:41:46 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/15 12:41:50 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *str);

void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*ft_strdup(const char *s1);

char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd);

struct Node
{
	char *data;
	struct Node* next;
};

struct Node* append(struct Node* head, char* str);
