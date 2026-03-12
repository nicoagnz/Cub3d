/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:59:16 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/12 12:59:30 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*pixel;

	if (!tex || x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (0x00FF00FF);
	pixel = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	return ((pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
}

static mlx_texture_t	*get_texture(t_game *game, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (dda->step_x > 0)
			return (game->config_map.texture_ea);
		return (game->config_map.texture_we);
	}
	if (dda->step_y > 0)
		return (game->config_map.texture_so);
	return (game->config_map.texture_no);
}

static int	calc_tex_x(t_game *game, t_dda *dda, mlx_texture_t *tex,
				double perp_dist)
{
	double	wall_x;
	int		tex_x;

	if (dda->side == 0)
		wall_x = game->player.y + perp_dist * dda->ray_dir_y;
	else
		wall_x = game->player.x + perp_dist * dda->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)tex->width);
	if (dda->side == 0 && dda->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (dda->side == 1 && dda->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static void	draw_column_texture(t_game *game, int x, mlx_texture_t *tex,
				int data[3], int line_height)
{
	double		step;
	double		tex_pos;
	int			y;
	uint32_t	color;
	int			tex_y;

	step = 1.0 * tex->height / line_height;
	tex_pos = (data[0] - game->win_h / 2 + line_height / 2) * step;
	y = data[0];
	while (y <= data[1])
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		color = get_texture_pixel(tex, data[2], tex_y);
		mlx_put_pixel(game->frame.img, x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_texture(t_game *game, int x, t_dda *dda, int limits[2],
				double perp_dist)
{
	mlx_texture_t	*tex;
	int				data[3];
	int				line_height;

	tex = get_texture(game, dda);
	line_height = (int)(game->win_h / perp_dist);
	data[0] = limits[0];
	data[1] = limits[1];
	data[2] = calc_tex_x(game, dda, tex, perp_dist);
	draw_column_texture(game, x, tex, data, line_height);
}
