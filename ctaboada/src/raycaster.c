#include "../includes/cub3d.h"

static void init_ray(t_game *game, int x,double *ray_dir_x, double *ray_dir_y)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)game->win_w - 1.0; // x-coordinate in camera space
	*ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	*ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
}
static void init_dda(t_game *game, double ray_dir_x,double ray_dir_y, t_dda *dda)
{
	dda->map_x = (int)game->player.x;
	dda->map_y = (int)game->player.y;
	dda->delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
	dda->delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
	init_dda_step(game, ray_dir_x, ray_dir_y, dda);
}
static void run_dda(t_game *game, t_dda *dda)
{
	while(1)
	{
		if(dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if(is_wall_cell(game,dda->map_x, dda->map_y))
			break ;
	}
}

static void	draw_column(t_game *game, int x, t_dda *dda, int win_h,
				double ray_dir_x, double ray_dir_y)
{
	int		limits[2];
	double	ray_dir[2];
	double	perp_dist;
	int		line_height;

	perp_dist = compute_perp_dist(game, dda, ray_dir_x, ray_dir_y);
	line_height = (int)(win_h / perp_dist);
	limits[0] = -line_height / 2 + win_h / 2;
	limits[1] = line_height / 2 + win_h / 2;
	if (limits[0] < 0)
		limits[0] = 0;
	if (limits[1] >= win_h)
		limits[1] = win_h - 1;
	ray_dir[0] = ray_dir_x;
	ray_dir[1] = ray_dir_y;
	draw_texture(game, x, dda, limits, ray_dir, perp_dist);
}
void	render_walls(t_game *game)
{
	int		x;
	double	ray_dir_x;
	double	ray_dir_y;
	t_dda	dda;

	if(!game || !game->mlx || !game->map || !game->map->map)
		return ;
	x = 0;
	while (x < game->win_w)
	{
		init_ray(game, x, &ray_dir_x, &ray_dir_y);
		init_dda(game, ray_dir_x, ray_dir_y, &dda);
		run_dda(game, &dda);
		draw_column(game, x, &dda, game->win_h, ray_dir_x, ray_dir_y);
		x++;
	}
}