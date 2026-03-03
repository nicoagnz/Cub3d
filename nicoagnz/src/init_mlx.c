#include "../includes/cub3d.h"

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(*game));
	game->win_w = 1024;
	game->win_h = 768;
}

void	init_mlx(t_game *game)
{
	validate_render_contract(game);
	game->mlx = mlx_init(game->win_w, game->win_h, "Cub3D", true);
	if (!game->mlx)
		ft_validate_error("Error\nFailed to initialize MLX");
	game->frame.img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!game->frame.img)
		ft_validate_error("Error\nFailed to create frame image");
	if(mlx_image_to_window(game->mlx, game->frame.img, 0, 0) < 0)
		ft_validate_error("Error\nFailed to put attach frame to window");
	render_base(game);
}
void	start_game(t_game *game)
{
	mlx_loop(game->mlx);
}