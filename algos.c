/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehell <ehell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 18:39:04 by ehell             #+#    #+#             */
/*   Updated: 2020/02/07 18:17:20 by ehell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_koord	**malloc_massiv(int x, int y)
{
	int		i;
	t_koord	**massive;

	i = 0;
	if (!(massive = (t_koord**)(malloc(sizeof(t_koord**) * y))))
		return (NULL);
	while (i < y)
	{
		if (!(massive[i] = (t_koord*)(malloc(sizeof(t_koord) * x))))
			return (NULL);
		i++;
	}
	return (massive);
}

void	parser(int fd, t_koord **massive)
{
	char	*line;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (get_next_line(fd, &line))
	{
		j = 0;
		k = 0;
		while (line[j])
		{
			if (line[j] != ' ')
			{
				massive[i][k].old_z = ft_atoi(&(line[j]));
				k++;
				while (line[j] != ' ' && line[j])
					j++;
			}
			else
				j++;
		}
		i++;
		free(line);
	}
}

void	try_to_print(t_koord **massive, t_app *app)
{
	int i;
	int j;

	i = 0;
	ft_bzero(app->dadr, (app->width) * app->height * (app->bpp / 8));
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			if (j + 1 < app->max_x)
				draw(massive[i][j], massive[i][j + 1], app);
			if (i + 1 < app->max_y)
				draw(massive[i][j], massive[i + 1][j], app);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->im_ptr, 200, 0);
}

t_koord	**read_tomass(int len_x, int len_y, int fd)
{
	t_koord **massive;
	int		i;
	int		j;

	i = 0;
	j = 0;
	massive = malloc_massiv(len_x, len_y);
	parser(fd, massive);
	return (massive);
}

void	setuper(t_app *app)
{
	mlx_key_hook(app->win_ptr, event_key, app);
}
