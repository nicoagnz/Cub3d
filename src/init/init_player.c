#include "../includes/cub3d.h"

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_orientation(t_player *p, char spawn)
{
	if (spawn == 'N')
	{
		p->dir_x = 0.0;
		p->dir_y = -1.0;
		p->plane_x = 0.66;
		p->plane_y = 0.0;
	}
	else if (spawn == 'S')
	{
		p->dir_x = 0.0;
		p->dir_y = 1.0;
		p->plane_x = -0.66;
		p->plane_y = 0.0;
	}
	else if (spawn == 'E')
	{
		p->dir_x = 1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = 0.66;
	}
	else if (spawn == 'W')
	{
		p->dir_x = -1.0;
		p->dir_y = 0.0;
		p->plane_x = 0.0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	int		spawn_count;
	char	c;

	if (!game || !game->map || !game->map->map)
		ft_validate_error("Error\nPlayer init: map not initialized");
	spawn_count = 0;
	y = 0;
	while (y < game->map->map_height && game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			c = game->map->map[y][x];
			if (is_spawn(c))
			{
				spawn_count++;
				if (spawn_count > 1)
					ft_validate_error("Error\nPlayer init: multiple spawns");
				game->player.x = (double)x + 0.5;
				game->player.y = (double)y + 0.5;
				set_player_orientation(&game->player, c);
				game->map->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
		ft_validate_error("Error\nPlayer init: missing spawn");
}