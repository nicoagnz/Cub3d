/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:47:28 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/12 10:35:32 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parser_map(t_game *game, char *file)
{
	char	**file_lines;

	file_lines = ft_read_file(file);
	ft_parse_file(game, file_lines);
	ft_validate_config(game);
	ft_validate_map(game);
	ft_free_split(file_lines);
}
