/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:14:13 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/03 12:51:35 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	ft_is_config_line(char *line)
{
	char *p;

	p = ft_skip_spaces(line);
	if (!p || *p == '\0')
		return (0);
	if ((ft_strncmp(p, "NO", 2) == 0
		|| ft_strncmp(p, "SO", 2) == 0
		|| ft_strncmp(p, "WE", 2) == 0
		|| ft_strncmp(p, "EA", 2) == 0)
		&& ft_is_space(p[2]))
		return (1);
	if ((p[0] == 'F' || p[0] == 'C') && ft_is_space(p[1]))
		return (1);
	return (0);
}

static int	ft_config_complete(t_config *config)
{
	if (!config->no_set || !config->so_set || !config->we_set 
		|| !config->ea_set || !config->floor_set || !config->ceiling_set)
		return (0);
	return (1);
}

void ft_parse_file(t_game *game, char **lines)
{
	char	*line;							// Si no se mete al while (lines[i]) no estaria inicializado
	int		i = 0;

	i = 0;
	while (lines[i])
	{
		line = lines[i];
		line = ft_skip_spaces(lines[i]);
		if (*line == '\0')
			;
		else if (ft_is_config_line(line))
			ft_parse_config_line(game, line);
		else if (ft_is_map_line(line))
		{
			if (!ft_config_complete(&game->config_map))
				ft_parser_error("Map found before config complete", game);
			ft_parse_map(game, lines, i);
			return;
		}
		else
			ft_parser_error("Invalid line in config section", game);
		i++;
	}
	ft_parser_error("No map found", game);
}

// void ft_parse_file(t_game *game, char **lines)
// {
// 	char	*line;                            // Si no se mete al while (lines[i]) no estaria inicializado
// 	int		i = 0;
// 	int		seen_config = 0;
// 	int		had_blank = 0;

// 	i = 0;
// 	while (lines[i])
// 	{
// 		line = ft_skip_spaces(lines[i]);
// 		if (*line == '\0')
// 		{
// 			if (seen_config)
// 				had_blank = 1;
// 		}
// 		else if (ft_is_config_line(line))
// 		{
// 			ft_parse_config_line(game, line);
// 			seen_config = 1;
// 			had_blank = 0;
// 		}
// 		else if (ft_is_map_line(lines[i]))
// 		{
// 			if (!ft_config_complete(&game->config_map))
// 				ft_parser_error("Map found before config complete", game);
// 			if (!had_blank && seen_config)
// 				ft_parser_error("Missing empty line between config and map", game);
// 			ft_parse_map(game, lines, i);
// 			return;
// 		}
// 		else
// 			ft_parser_error("Invalid line in config section", game);
// 		i++;
// 	}
// 	ft_parser_error("No map found", game);
// }
