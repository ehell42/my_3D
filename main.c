/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexzudin <alexzudin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:18 by aguiller          #+#    #+#             */
/*   Updated: 2020/01/31 19:46:53 by alexzudin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		checkarg(int argc, char **argv)
{
	int fd;

	if (argc <= 1)
	{
		ft_putendl("Usage : ./fdf <filename> [ case_size z_size ]");
		return (0);
	}
	if (argc > 4)
	{
		ft_putendl("Usage : ./fdf <filename> [ case_size z_size ]");
		return (0);
	}
	fd = open(argv[1], O_RDWR);
	if (fd <= 0)
	{
		ft_putendl("Could not to open the file");
		return (0);
	}
	return (fd);
}

int err()
{
	ft_putendl("error");
	return (0);
}

int working(int fd, int len_x, int len_y)
{
	t_app	*app;
	t_koord **massive;

	massive = read_tomass(len_x, len_y, fd);
	app = app_init(massive, len_x, len_y);
	to_iso(massive, app);
    try_to_print(massive, app);
	setuper(app);
	mlx_loop(app->mlx_ptr);
	return (0);

}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		len_x;
	int		len_y;
	
	line = NULL;
	if ((fd = checkarg(argc, argv)) == 0)
		return (0);
	if ((len_y = valid_onlydigits(fd)) < 0)
		return(err());
	if (close(fd) < 0)
		return(err());
	if ((fd = checkarg(argc, argv)) < 0)
		return(err());
	if ((len_x = valid_for_count(fd, line)) < 0)
		return(err());
	if (close(fd) < 0)
		return(err());
	if ((fd = checkarg(argc, argv)) < 0)
		return(err());
	working(fd, len_x, len_y);
	return (0);
}
