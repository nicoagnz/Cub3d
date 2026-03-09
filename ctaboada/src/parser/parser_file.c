/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaboada <ctaboada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:14:13 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/02 11:43:06 by ctaboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

static int	is_empty_line(char *line)
{
	char	*p;

	p = skip_spaces(line);
	return (*p == '\0' || *p == '\n');
}

static int	is_config_line(char *line)
{
	char	*p;

	p = skip_spaces(line);
	if (ft_strncmp(p, "NO", 2) == 0 || ft_strncmp(p, "SO", 2) == 0
		|| ft_strncmp(p, "WE", 2) == 0 || ft_strncmp(p, "EA", 2) == 0)
		return (1);
	if (*p == 'F' || *p == 'C')
		return (1);
	return (0);
}

static int	is_map_line(char *line)
{
	char	*p;

	p = line;
	if (*p == '\0')
		return (0);
	while (*p && *p != '\n')
	{
		if (*p != ' ' && *p != '0' && *p != '1' && *p != 'N'
			&& *p != 'S' && *p != 'E' && *p != 'W')
			return (0);
		p++;
	}
	return (1);
}

static int	config_complete(t_config *config)
{
	return (config->no_set && config->so_set && config->we_set
		&& config->ea_set && config->floor_set && config->ceiling_set);
}

static char	*dup_line_no_newline(char *line)
{
	char	*dup;
	int		len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	dup = malloc((size_t)len + 1);
	if (!dup)
		ft_parser_error("Malloc failed", NULL);
	dup[len] = '\0';
	while (len-- > 0)
		dup[len] = line[len];
	return (dup);
}

static void	parse_color(int color[3], int *flag, char *p)
{
	int			r;
	int			g;
	int			b;
	char		trail;

	p = skip_spaces(p);
	if (*flag)
		ft_parser_error("Duplicate color definition", NULL);
	trail = '\0';
	if (sscanf(p, "%d,%d,%d %c", &r, &g, &b, &trail) != 3)
		ft_parser_error("Invalid color format", NULL);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_parser_error("Color values out of range [0-255]", NULL);
	color[0] = r;
	color[1] = g;
	color[2] = b;
	*flag = 1;
}

static void	parse_texture(char **tex_field, int *flag, char *p)
{
	char	*start;

	start = skip_spaces(p);
	if (*flag)
		ft_parser_error("Duplicate texture definition", NULL);
	if (*start == '\0' || *start == '\n')
		ft_parser_error("Texture path missing", NULL);
	*tex_field = dup_line_no_newline(start);
	if (!*tex_field)
		ft_parser_error("Malloc failed", NULL);
	*flag = 1;
}

static void	parse_config_line(t_game *game, char *line)
{
	char	*p;

	p = skip_spaces(line);
	if (ft_strncmp(p, "NO", 2) == 0)
		parse_texture(&game->config_map.tex_no, &game->config_map.no_set, p + 2);
	else if (ft_strncmp(p, "SO", 2) == 0)
		parse_texture(&game->config_map.tex_so, &game->config_map.so_set, p + 2);
	else if (ft_strncmp(p, "WE", 2) == 0)
		parse_texture(&game->config_map.tex_we, &game->config_map.we_set, p + 2);
	else if (ft_strncmp(p, "EA", 2) == 0)
		parse_texture(&game->config_map.tex_ea, &game->config_map.ea_set, p + 2);
	else if (*p == 'F')
		parse_color(game->config_map.floor_color, &game->config_map.floor_set, p + 1);
	else if (*p == 'C')
		parse_color(game->config_map.ceiling_color,
			&game->config_map.ceiling_set, p + 1);
	else
		ft_parser_error("Invalid config identifier", game);
}

static void	parse_map_section(t_game *game, char **lines, int start)
{
	int		count;
	int		i;
	int		j;
	char	**map;

	i = start;
	count = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		count++;
		i++;
	}
	if (count == 0)
		ft_parser_error("No map found", game);
	map = malloc(sizeof(char *) * ((size_t)count + 1));
	if (!map)
		ft_parser_error("Malloc failed", game);
	j = 0;
	while (j < count)
	{
		map[j] = dup_line_no_newline(lines[start + j]);
		j++;
	}
	map[count] = NULL;
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		ft_parser_error("Malloc failed", game);
	game->map->map = map;
	game->map->map_height = count;
	game->map->map_width = 0;
	j = 0;
	while (j < count)
	{
		i = (int)ft_strlen(map[j]);
		if (i > game->map->map_width)
			game->map->map_width = i;
		j++;
	}
}

void	ft_parse_file(t_game *game, char **lines)
{
	char	*line;
	int		i;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		if (is_empty_line(line))
		{
			i++;
			continue ;
		}
		if (is_config_line(line))
			parse_config_line(game, line);
		else if (is_map_line(line))
		{
			if (!config_complete(&game->config_map))
				ft_parser_error("Map found before config complete", game);
			parse_map_section(game, lines, i);
			return ;
		}
		else
			ft_parser_error("Invalid line in config section", game);
		i++;
	}
	ft_parser_error("No map found", game);
}

void	ft_validate_game(t_game *game)
{
	if (!game || !game->map || !game->map->map)
		ft_parser_error("Invalid game data", game);
	if (!config_complete(&game->config_map))
		ft_parser_error("Incomplete config", game);
	if (game->map->map_height <= 0 || game->map->map_width <= 0)
		ft_parser_error("Invalid map size", game);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
