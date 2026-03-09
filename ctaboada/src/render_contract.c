#include "../includes/cub3d.h"

static int	is_rgb_valid(int c[3])
{
	return (c[0] >= 0 && c[0] <= 255
		&& c[1] >= 0 && c[1] <= 255
		&& c[2] >= 0 && c[2] <= 255);
}

void	validate_render_contract(t_game *game)
{
	if (!game || !game->map || !game->map->map)
		ft_validate_error("Error\nRender contract: map not initialized");
	if (game->map->map_width <= 0 || game->map->map_height <= 0)
		ft_validate_error("Error\nRender contract: invalid map size");
	if (!is_rgb_valid(game->config_map.floor_color))
		ft_validate_error("Error\nRender contract: invalid floor color");
	if (!is_rgb_valid(game->config_map.ceiling_color))
		ft_validate_error("Error\nRender contract: invalid ceiling color");
	if (!game->config_map.tex_no || !game->config_map.tex_so
		|| !game->config_map.tex_we || !game->config_map.tex_ea)
		ft_validate_error("Error\nRender contract: missing textures");
}
