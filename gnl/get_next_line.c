/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:39:18 by mhiguera          #+#    #+#             */
/*   Updated: 2023/12/04 19:41:46 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(int fd, char *aux)
{
	int		save_read;
	char	*bufstr;

	save_read = 1;
	bufstr = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!bufstr)
		return (NULL);
	while (!ft_strchr(aux, '\n') && save_read != 0)
	{
		save_read = read(fd, bufstr, BUFFER_SIZE);
		if (save_read == -1)
		{
			free(bufstr);
			return (NULL);
		}
		bufstr[save_read] = '\0';
		aux = ft_strjoin2(aux, bufstr);
	}
	free(bufstr);
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*aux[4096];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	aux[fd] = ft_save(fd, aux[fd]);
	if (!aux[fd])
	{
		free(aux[fd]);
		return (NULL);
	}
	str = ft_ending(aux[fd]);
	aux[fd] = ft_extra(aux[fd]);
	return (str);
}
/*
int main()
{
	int fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	system("leaks a.out");
	return (0);
}
*/