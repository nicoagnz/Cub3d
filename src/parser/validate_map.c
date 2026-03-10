/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:06:19 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/10 10:44:16 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_set_map_dimensions(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->map[i])
		i++;
	game->map->map_height = i;
	game->map->map_width = ft_strlen(game->map->map[0]);
}

void	ft_validate_map_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
		{
			if (!ft_valid_map_char(game->map->map[y][x]))
				ft_parser_error("Invalid map character", game);
			x++;
		}
		y++;
	}
}

void	ft_validate_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
		{
			if (ft_strchr("NSEW", game->map->map[y][x]))
			{
				game->player.x = x;
				game->player.y = y;
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		ft_parser_error("Map must contain exactly one player", game);
}

static void	ft_validate_map_closed(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
		{
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
