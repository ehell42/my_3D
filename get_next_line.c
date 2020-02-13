/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehell <ehell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 08:10:16 by alexzudin         #+#    #+#             */
/*   Updated: 2020/02/07 18:57:26 by ehell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	makeline(char **line, char **longm, int fd, int schitali)
{
	int		i;
	char	*mem;

	i = 0;
	while (longm[fd][i] != '\n' && longm[fd][i] != '\0')
		i++;
	if (longm[fd][i] == '\n')
	{
		*line = ft_strsub(longm[fd], 0, i);
		mem = ft_strdup(longm[fd] + i + 1);
		free(longm[fd]);
		longm[fd] = mem;
		if (longm[fd][0] == '\0')
			ft_strdel(&(longm[fd]));
	}
	else
	{
		if (schitali == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strsub(longm[fd], 0, i);
		ft_strdel(&(longm[fd]));
	}
	return (1);
}

int	reading(char **longm, int fd)
{
	char	bufer[BUFF_SIZE + 1];
	int		status;
	char	*mem;
	int		i;

	mem = NULL;
	while ((status = read(fd, bufer, BUFF_SIZE)) > 0)
	{
		i = status;
		while (i < BUFF_SIZE + 1)
			bufer[i++] = '\0';
		if (longm[fd] == NULL)
			longm[fd] = ft_strnew(0);
		mem = ft_strjoin(longm[fd], bufer);
		free(longm[fd]);
		longm[fd] = mem;
		mem = NULL;
		if (ft_strchr(longm[fd], '\n'))
			break ;
	}
	return (status);
}

int	get_next_line(const int fd, char **line)
{
	static char	*longmem[400];
	int			status;
	int			r;

	if (fd < 0 || line == NULL)
		return (-1);
	status = reading(longmem, fd);
	if (status < 0)
		return (-1);
	if (status == 0 && longmem[fd] == NULL)
		return (0);
	r = makeline(line, longmem, fd, status);
	return (r);
}
