#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mlx.h"

struct  s_koord
{
    int x;
    int y;
};

void brezen_alg(struct s_koord point1, struct s_koord point2, void *mlx_ptr, void *win_ptr)
{
    int err;
    int diry;
    struct s_koord point;
  
    point = point1;
    err = 0;
    if (point2.y - point1.y >= 0)
        diry = 1;
    if (point2.y - point1.y < 0)
        diry = -1;
    while (point.x <= point2.x)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, point.x, point.y, 0xFFFFFF);
        err = err + abs(point1.y - point2.y) + 1;
        if (err >= abs(point1.x - point2.x) + 1)
        {
            point.y = point.y + diry;
            err = err - (abs(point1.x - point2.x) + 1);
        }
        point.x++;
    }
}

int main()
{
    void    *mlx_ptr;
    void    *win_ptr;
    int     i;
    struct s_koord point1;
    struct s_koord point2;

    point1.x = 0;
    point1.y = 15;
    point2.x = 300;
    point2.y = 200;
    i = 50;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
    brezen_alg(point1, point2, mlx_ptr, win_ptr);
    mlx_pixel_put(mlx_ptr, win_ptr, 100, 51, 0xFFFFFF);
    mlx_string_put(mlx_ptr,win_ptr, 250, 250, 0xFFFFFF, "mass");
    mlx_loop(mlx_ptr);
}