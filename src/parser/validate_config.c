/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:29:31 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/12 10:55:12 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	validate_color_range(int color[3], t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			ft_parser_error("Color out of range", game);
		i++;
	}
}

static void	validate_colors(t_config *cfg, t_game *game)
{
	if (!cfg->floor_set || !cfg->ceiling_set)
		ft_parser_error("Missing floor or ceiling color", game);
	validate_color_range(cfg->floor_color, game);
	validate_color_range(cfg->ceiling_color, game);
}

static void	validate_textures(t_config *cfg, t_game *game)
{
	if (!cfg->tex_no || !cfg->tex_so
		|| !cfg->tex_we || !cfg->tex_ea)
		ft_parser_error("Missing texture", game);
	if (*cfg->tex_no == '\0'
		|| *cfg->tex_so == '\0'
		|| *cfg->tex_we == '\0'
		|| *cfg->tex_ea == '\0')
		ft_parser_error("Empty texture path", game);
}

void	ft_validate_config(t_game *game)
{
	validate_textures(&game->config_map, game);
	validate_colors(&game->config_map, game);
}
