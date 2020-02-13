/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehell <ehell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:06:06 by alexzudin         #+#    #+#             */
/*   Updated: 2020/02/10 16:30:04 by ehell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_app	*app_init(t_koord **massive, int x, int y, int endian)
{
	t_app	*app;

	app = (t_app*)malloc(sizeof(t_app));
	if (!(app->mlx_ptr = mlx_init()))
		return (NULL);
	app->width = 1200;
	app->height = 1000;
	app->zoom = 10;
	app->max_x = x;
	app->max_y = y;
	app->bpp = 16;
	app->px = 0;
	app->py = 0;
	app->projection = 'I';
	app->size_line = app->bpp * app->max_x * app->zoom;
	if (!(app->im_ptr = mlx_new_image(app->mlx_ptr, app->width, app->height)))
		return (NULL);
	if (!(app->dadr = mlx_get_data_addr(app->im_ptr, &app->bpp, &app->size_line,
	&endian)) || !(app->win_ptr = mlx_new_window(app->mlx_ptr,
	app->width, app->height, "fdf")))
		return (NULL);
	app->massive = massive;
	return (app);
}

void	rotate(t_app *app)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			x = app->massive[i][j].old_x;
			app->massive[i][j].old_x = (x * cos(app->beta) -
			app->massive[i][j].old_y * sin(app->beta));
			app->massive[i][j].old_y = (x * sin(app->beta) +
			app->massive[i][j].old_y * cos(app->beta));
			j++;
		}
		i++;
	}
}

void	make_old(t_app *app)
{
	int	i;
	int	j;

	i = 0;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			app->massive[i][j].old_x = j * app->zoom;
			app->massive[i][j].old_y = i * app->zoom;
			j++;
		}
		i++;
	}
}

void	to_iso(t_koord **massive, t_app *app)
{
	int	i;
	int	j;

	i = 0;
	if (app->zoom < 0)
		app->zoom = 0;
	make_old(app);
	if (app->beta != 0)
		rotate(app);
	i = 0;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			massive[i][j].new_x = app->max_y * cos(0.523599) * app->f_zoom +
			(massive[i][j].old_x - massive[i][j].old_y) * cos(0.523599);
			massive[i][j].new_y = app->max_z * app->f_zoom +
			(-massive[i][j].old_z * app->zoom + (massive[i][j].old_x +
			massive[i][j].old_y) * sin(0.523599));
			j++;
		}
		i++;
	}
}

void	to_paralell(t_koord **massive, t_app *app)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (app->zoom < 0)
		app->zoom = 0;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			massive[i][j].new_x = 250 + j * app->zoom;
			massive[i][j].new_y = 400 + i * app->zoom;
			j++;
		}
		i++;
	}
}
