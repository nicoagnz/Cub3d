/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:25:51 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/02 10:59:41 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_validate_error(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit (1);
}

void	ft_parser_error(char *error_msg, t_game *game)
{
	ft_putendl_fd(error_msg, 2);
	if (game)
		ft_free_game(game);
	exit (1);
}
