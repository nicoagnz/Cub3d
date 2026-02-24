/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:47:28 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/24 12:13:50 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void parser_map(t_game *game, char *file)
{
	char **file_lines;

	file_lines = ft_read_file(file);
	ft_parse_file(game, file_lines);
	ft_validate_game(game);
	ft_free_split(file_lines);
}
