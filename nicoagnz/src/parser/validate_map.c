/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:06:19 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/05 13:22:59 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_valid_map_char(char c)
{
	if (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	ft_validate_map_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (!ft_valid_map_char(game->map->map[y][x]))
				ft_parser_error("Invalid map character", game);
			x++;
		}
		y++;
	}
}

static void	ft_validate_map_shape(t_game *game)
{
	int	i;
	int	width;

	i = 0;
	width = ft_strlen(game->map->map[0]);
	while (game->map->map[i])
	{
		if ((int)ft_strlen(game->map->map[i]) != width)
			ft_parser_error("Map must be rectangular", game);
		i++;
	}
	game->map->width = width;
	game->map->height = i;
}

static void	ft_validate_map_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map->width)
	{
		if (game->map->map[0][x] != '1'
			|| game->map->map[game->map->height - 1][x] != '1')
			ft_parser_error("Map not closed by walls", game);
		x++;
	}

	y = 0;
	while (y < game->map->height)
	{
		if (game->map->map[y][0] != '1'
			|| game->map->map[y][game->map->width - 1] != '1')
			ft_parser_error("Map not closed by walls", game);
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
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (ft_strchr("NSEW", game->map->map[y][x]))
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		ft_parser_error("Map must contain exactly one player", game);
}

void	ft_validate_map(t_game *game)
{
	ft_validate_map_shape(game);
	ft_validate_map_chars(game);
	ft_validate_map_walls(game);
	ft_validate_player(game);
}
