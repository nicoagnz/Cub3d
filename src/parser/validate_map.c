/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:06:19 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/12 11:02:13 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_check_cell(t_game *game, int x, int y)
{
	char	c;

	c = game->map->map[y][x];
	if (c == '0' || ft_strchr("NSEW", c))
	{
		if (y == 0 || x == 0
			|| y == game->map->map_height - 1
			|| x == game->map->map_width - 1)
			ft_parser_error("Map not closed", game);
		if (game->map->map[y - 1][x] == ' '
			|| game->map->map[y + 1][x] == ' '
			|| game->map->map[y][x - 1] == ' '
			|| game->map->map[y][x + 1] == ' ')
			ft_parser_error("Map not closed", game);
	}
}

static void	ft_validate_map_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
		{
			ft_check_cell(game, x, y);
			x++;
		}
		y++;
	}
}

void	ft_validate_map(t_game *game)
{
	ft_set_map_dimensions(game);
	ft_validate_map_chars(game);
	ft_validate_player(game);
	ft_validate_map_closed(game);
}
