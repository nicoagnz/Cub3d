/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:47:28 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/03 12:54:29 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void parser_map(t_game *game, char *file)
{
	char **file_lines;

	file_lines = ft_read_file(file);

	ft_parse_file(game, file_lines);      // parsea config + mapa

	ft_validate_config(game);             // valida coherencia config

	ft_validate_map(game);                // valida estructura mapa

	ft_free_split(file_lines);
}

//	FALTA:

//	Que me de error si mi despues de la config no hay un salto de linea
//	antes de entrar al mapa, ademas de que no haya configuracion doble.
