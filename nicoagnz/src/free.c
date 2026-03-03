/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:49:22 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/03 11:52:02 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_partial_map(char **map, int filled)
{
	while (filled > 0)
		free(map[--filled]);
	free(map);
}

void ft_free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	ft_free_game(t_game *game)
{
	if (!game)
		return;

	/* liberar texturas si se alocaron */
	if (game->config_map.tex_no)
		free(game->config_map.tex_no);
	if (game->config_map.tex_so)
		free(game->config_map.tex_so);
	if (game->config_map.tex_we)
		free(game->config_map.tex_we);
	if (game->config_map.tex_ea)
		free(game->config_map.tex_ea);

	/* liberar mapa y estructura de mapa */
	if (game->map)
	{
		if (game->map->map)
			ft_free_split(game->map->map);
		free(game->map);
	}
}
