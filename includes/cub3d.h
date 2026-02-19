/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:35 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/19 10:53:52 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

typedef enum e_validate_error
{
	VALIDATE_OK,
	VALIDATE_ERROR
}	t_validate_error;

typedef struct s_game
{
	// Aquí irán los campos necesarios para el juego, como el mapa, la posición del jugador, etc.
}	t_game;

int ft_validate_args(int ac, char **av);
int ft_error_handler(char *error_msg);
int	ft_openfd(char *file);

#endif