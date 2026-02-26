/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 12:14:13 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/26 12:54:27 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void parse_color(int color[3], int *flag, char *p)
{
	int r, g, b;
	char *tmp;

	p = skip_spaces(p);

	if (*flag)
		error_exit("Duplicate color definition", NULL);

	tmp = p;

	// Esperamos formato R,G,B sin espacios intermedios
	if (sscanf(tmp, "%d,%d,%d", &r, &g, &b) != 3)
		error_exit("Invalid color format", NULL);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Color values out of range [0-255]", NULL);

	color[0] = r;
	color[1] = g;
	color[2] = b;

	*flag = 1;

	// Verificar que no haya tokens extra después
	// Avanzamos tmp para saltar los dígitos y comas
	while (*tmp && (*tmp == ' ' || *tmp == '\t' || (*tmp >= '0' && *tmp <= '9') || *tmp == ','))
		tmp++;
	if (*tmp != '\0')
		error_exit("Extra token after color", NULL);
}

static void parse_texture(char **tex_field, int *flag, char *p)
{
	p = skip_spaces(p);

	if (*flag)
		error_exit("Duplicate texture definition", NULL); // NULL o game según tu diseño

	if (*p == '\0')
		error_exit("Texture path missing", NULL);

	// opcional: validar que path termina con extensión si quieres

	*tex_field = ft_strdup(p); // recuerda free luego
	if (!*tex_field)
		error_exit("Malloc failed", NULL);

	*flag = 1;

	// Verificar que no haya tokens extra (p. ej. espacios adicionales después del path)
	char *end = skip_spaces(p + ft_strlen(p));
	if (*end != '\0')
		error_exit("Extra token after texture path", NULL);
}

static char *skip_spaces(char *str)
{
	while (ft_is_space(*str))
		str++;
	return str;
}

static void parse_config_line(t_game *game, char *line)
{
	char *p;

	p = skip_spaces(line);

	// TEXTURAS
	if (ft_strncmp(p, "NO", 2) == 0)
		parse_texture(&game->config_map.tex_no, &game->config_map.no_set, p + 2);
	else if (ft_strncmp(p, "SO", 2) == 0)
		parse_texture(&game->config_map.tex_so, &game->config_map.so_set, p + 2);
	else if (ft_strncmp(p, "WE", 2) == 0)
		parse_texture(&game->config_map.tex_we, &game->config_map.we_set, p + 2);
	else if (ft_strncmp(p, "EA", 2) == 0)
		parse_texture(&game->config_map.tex_ea, &game->config_map.ea_set, p + 2);

	// COLORES
	else if (p[0] == 'F')
		parse_color(game->config_map.floor_color, &game->config_map.floor_set, p + 1);
	else if (p[0] == 'C')
		parse_color(game->config_map.ceiling_color, &game->config_map.ceiling_set, p + 1);
	else
		error_exit("Invalid config identifier", game);
}

void ft_parse_file(t_game *game, char **lines)
{
	char	*line;
	t_parse_state state = PARSE_CONFIG;
	int		i = 0;

	i = 0;
	state = PARSE_CONFIG;
	while (lines[i])
	{
		line = lines[i];
		if (state == PARSE_CONFIG)
		{
			while (*line == ' ' || *line == '\t')
				line++;
			if (*line == '\0')
				;

			else if (ft_is_config_line(line))
				ft_parse_config_line(game, line);

			else if (ft_is_map_line(line))
			{
				if (!ft_config_complete(&game->config_map))
					ft_parser_error("Map found before config complete", game);
				ft_parse_map_section(game, lines, i);
				return;
			}
			else
				ft_parser_error("Invalid line in config section", game);
		}
		i++;
	}
	if (!line)
		line = NULL;
	ft_parser_error("No map found", game);
}

// Funciones auxiliares por estudiar
