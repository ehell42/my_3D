/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehell <ehell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 11:25:25 by alexzudin         #+#    #+#             */
/*   Updated: 2020/02/10 16:20:56 by ehell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_app *app, int x, int y, char colour)
{
	char	*mass;
	int		i;

	mass = app->dadr;
	i = app->size_line * y + x * (app->bpp / 8);
	mass[i] = 0xAA;
	mass[++i] = colour;
	mass[++i] = colour;
}

void	draw_for_horizontal(t_koord point0, t_koord point1, t_app *app)
{
	int		err;
	int		diry;
	t_koord	point;

	point = point0;
	err = 0;
	if (point1.new_y - point0.new_y >= 0)
		diry = 1;
	else
		diry = -1;
	while (point.new_x <= point1.new_x)
	{
		if (point.new_x + app->px < app->width &&
		point.new_y + app->py < app->height && point.new_x + app->px >= 0
		&& point.new_y + app->py >= 0)
			pixel_put(app, point.new_x + app->px, point.new_y + app->py,
			color(point0, point1, (point.old_z - point0.old_z)));
		err = err + abs(point0.new_y - point1.new_y) + 1;
		if (err >= abs(point0.new_x - point1.new_x) + 1)
		{
			point.new_y = point.new_y + diry;
			err = err - (abs(point0.new_x - point1.new_x) + 1);
		}
		point.new_x++;
	}
}

void	draw_for_vertical(t_koord point0, t_koord point1, t_app *app)
{
	int		err;
	int		diry;
	t_koord	point;

	point = point0;
	err = 0;
	if (point1.new_x - point0.new_x >= 0)
		diry = 1;
	else
		diry = -1;
	while (point.new_y <= point1.new_y)
	{
		if (point.new_x + app->px < app->width &&
		point.new_y + app->py < app->height &&
		point.new_x + app->px >= 0 && point.new_y + app->py >= 0)
			pixel_put(app, point.new_x + app->px, point.new_y + app->py,
			color(point0, point1, (point.new_y - point0.new_y)));
		err = err + abs(point0.new_x - point1.new_x) + 1;
		if (err >= abs(point0.new_y - point1.new_y) + 1)
		{
			point.new_x = point.new_x + diry;
			err = err - (abs(point0.new_y - point1.new_y) + 1);
		}
		point.new_y++;
	}
}

void	draw(t_koord point0, t_koord point1, t_app *app)
{
	int dx;
	int dy;

	dx = point1.new_x - point0.new_x;
	dy = point1.new_y - point0.new_y;
	if (abs(dx) > abs(dy))
	{
		if (point0.new_x > point1.new_x)
			draw_for_horizontal(point1, point0, app);
		else
			draw_for_horizontal(point0, point1, app);
	}
	else
	{
		if (point0.new_y > point1.new_y)
			draw_for_vertical(point1, point0, app);
		else
			draw_for_vertical(point0, point1, app);
	}
}
