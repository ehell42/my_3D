/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehell <ehell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:26:57 by aguiller          #+#    #+#             */
/*   Updated: 2020/02/10 16:32:20 by ehell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stdio.h"

void	find_min_max(t_koord **massive, t_app *app)
{
	int	i;
	int	j;
	int	min;
	int	max;

	i = 0;
	min = 2147483647;
	max = -214783648;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			if (massive[i][j].old_z < min)
				min = massive[i][j].old_z;
			if (massive[i][j].old_z > max)
				max = massive[i][j].old_z;
			j++;
		}
		i++;
	}
	app->min_z = min;
	app->max_z = max;
}

void	color_for_all(t_app *app)
{
	int		i;
	int		j;
	double	proc1;
	double	proc2;
	double	proc3;

	i = 0;
	j = 0;
	while (i < app->max_y)
	{
		j = 0;
		while (j < app->max_x)
		{
			proc1 = (app->massive[i][j].old_z - app->min_z);
			proc2 = (app->max_z - app->min_z);
			proc3 = proc1 / proc2;
			app->massive[i][j].color = 0x10 + proc3 * (0xFF - 0x10);
			j++;
		}
		i++;
	}
}

char	color(t_koord p1, t_koord p2, int i)
{
	char	ret;
	double	temp;
	double	tmp;

	if (p1.old_z == p2.old_z)
		return (p1.color);
	else
	{
		tmp = (p2.new_y - p1.new_y);
		temp = i / tmp;
		ret = p1.color + temp * (p2.color - p1.color);
		return (ret);
	}
}

int		event_key_2(int key, t_app *app)
{
	if (key == 12)
		app->beta = app->beta - 0.05;
	if (key == 14)
		app->beta = app->beta + 0.05;
	return (reprint(app));
}
