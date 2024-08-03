/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_random.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khmessah <khmessah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 02:21:26 by khmessah          #+#    #+#             */
/*   Updated: 2024/08/03 08:54:06 by khmessah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*addtmpdir(char *name)
{
	char	*str;

	str = ft_strjoin1("/tmp/", name);
	free(name);
	return (str);
}

char	*nom_file(void)
{
	int		fd;
	char	*line;
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	fd = open("/dev/random", O_RDONLY);
	line = malloc(sizeof(char) * 11);
	if (!line)
		return (NULL);
	read(fd, line, 10);
	line[10] = '\0';
	s = malloc(sizeof(char) * 11);
	while (line[i])
	{
		s[j] = "0123456789abcdef"[(unsigned char)line[i] % 16];
		i++;
		j++;
	}
	s[j] = '\0';
	free(line);
	return (addtmpdir(s));
}
