/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaboada <ctaboada@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:00:00 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/27 12:45:45 by ctaboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game game;
	
	ft_validate_args(ac, av);
	init_game(&game);
	parser_map(&game, av[1]);
	init_player(&game);
	init_mlx(&game);
	start_game(&game);
	return (0);
}
