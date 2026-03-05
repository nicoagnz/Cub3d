/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:25:48 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/05 12:30:06 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_parse_color(t_game *game, int color[3], int *flag, char *p)
{
	char	**rgb;
	char	*num;
	int		i;

	p = ft_skip_spaces(p);
	if (*flag)
		ft_parser_error("Duplicate color definition", game);
	if (*p == '\0')
		ft_parser_error("Color missing", game);
	rgb = ft_split(p, ',');
	if (!rgb)
		ft_parser_error("Malloc failed", game);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		ft_free_split(rgb);
		ft_parser_error("Invalid color format", game);
	}
	i = 0;
	while (i < 3)
	{
		num = ft_skip_spaces(rgb[i]);
		if (!ft_str_isdigits(num))
		{
			ft_free_split(rgb);
			ft_parser_error("Color must be numeric", game);
		}
		color[i] = ft_atoi(num);
		i++;
	}
	ft_free_split(rgb);
	*flag = 1;
}

static void ft_parse_texture(t_game *game, char **tex_field, int *flag, char *p)
{
	char *start;
	char *end;
	char *path;

	p = ft_skip_spaces(p);
	if (*flag)
		ft_parser_error("Duplicate texture definition", game);
	if (*p == '\0')
		ft_parser_error("Texture path missing", game);
	start = p;
	while (*p && !ft_is_space(*p))
		p++;
	end = p;
	if (*p != '\0')
	{
		p = ft_skip_spaces(p);
		if (*p != '\0')
			ft_parser_error("Extra token after texture path", game);
	}
	path = ft_substr(start, 0, end - start);
	if (!path)
		ft_parser_error("Malloc failed", game);
	*tex_field = path;
	*flag = 1;
}

void ft_parse_config_line(t_game *game, char *line)
{
	char *p;

	p = ft_skip_spaces(line);
	if (ft_strncmp(p, "NO", 2) == 0)
		ft_parse_texture(game, &game->config_map.tex_no, &game->config_map.no_set, p + 2);
	else if (ft_strncmp(p, "SO", 2) == 0)
		ft_parse_texture(game, &game->config_map.tex_so, &game->config_map.so_set, p + 2);
	else if (ft_strncmp(p, "WE", 2) == 0)
		ft_parse_texture(game, &game->config_map.tex_we, &game->config_map.we_set, p + 2);
	else if (ft_strncmp(p, "EA", 2) == 0)
		ft_parse_texture(game, &game->config_map.tex_ea, &game->config_map.ea_set, p + 2);
	else if (p[0] == 'F')
		ft_parse_color(game, game->config_map.floor_color, &game->config_map.floor_set, p + 1);
	else if (p[0] == 'C')
		ft_parse_color(game, game->config_map.ceiling_color, &game->config_map.ceiling_set, p + 1);
	else
		ft_parser_error("Invalid config identifier", game);
}
