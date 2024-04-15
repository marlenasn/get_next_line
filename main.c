/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwiecek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:42:14 by mwiecek           #+#    #+#             */
/*   Updated: 2024/04/15 12:42:19 by mwiecek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
	int fd;
	char* s;
	fd = open("plik2.txt", O_RDONLY);
	while (1) {
		s = get_next_line(fd);
		if (!s) {
			return 0;
		}
		printf("%s", s);
	}
	// s = get_next_line(fd);
	// printf("%s", s);
	// s = get_next_line(fd);
	// printf("%s\n", s);
	// s = get_next_line(fd);
	//printf("%s\n", s);
	return 0;
}
