/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotina <nikotina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:28:00 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/09 10:43:08 by nikotina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int ft_get_map_height(char **lines, int start)
{
	int i;
	int height;
	char *trim;

	i = start;
	height = 0;
	while (lines[i])
	{
		trim = ft_skip_spaces(lines[i]);
		if (*trim != '\0' && !ft_is_map_line(lines[i]))
			return (-1);
		height++;
		i++;
	}
	return (height);
}

static int	ft_get_map_width(char **lines, int start, int height)
{
	int	i = 0;
	int	max = 0;
	int	len;

	while (i < height)
	{
		len = ft_strlen(lines[start + i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	**ft_rectangular_map(char **lines, int start, int height, int width)
{
	char	**map;
	int		i;
	int		len;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = malloc(width + 1);
		if (!map[i])
		{
			free_partial_map(map, i);
			return (NULL);
		}
		ft_memset(map[i], ' ', width);
		map[i][width] = '\0';
	len = ft_strlen(lines[start + i]);
	if (len > 0 && lines[start + i][len - 1] == '\n')
		len--;
	ft_memcpy(map[i], lines[start + i], len);
		i++;
	}
	map[height] = NULL;
	return (map);
}

static void	ft_check_no_extra(char **lines, int index, t_game *game)
{
	while (lines[index])
	{
		if (*ft_skip_spaces(lines[index]) != '\0')
			ft_parser_error("Extra content after map", game);
		index++;
	}
}

void	ft_parse_map(t_game *game, char **lines, int start)
{
	int	height;
	int	width;

	height = ft_get_map_height(lines, start);
	if (height <= 0)
		ft_parser_error("Invalid or empty map", game);
	width = ft_get_map_width(lines, start, height);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		ft_parser_error("Malloc failed", game);
	game->map->map = ft_rectangular_map(lines, start, height, width);
	if (!game->map->map)
		ft_parser_error("Malloc failed", game);
	game->map->map_height = height;
	game->map->map_width = width;
	ft_check_no_extra(lines, start + height, game);
}
