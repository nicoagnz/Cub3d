/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:35 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/26 12:14:41 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"

typedef enum e_parse_state
{
	PARSE_CONFIG,
	PARSE_MAP
}	t_parse_state;

typedef struct s_map
{
	char **map;
	int	map_width;
	int	map_height;
}	t_map;

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_color[3];
	int		ceiling_color[3];
	int		floor_set;
	int		ceiling_set;
	int		no_set;
	int		so_set;
	int		we_set;
	int		ea_set;
}	t_config;

typedef struct s_game
{
	t_map*			map;
	t_config		config_map;
}	t_game;

// VALIDATION
void	ft_validate_args(int ac, char **av);
int		ft_openfd(char *file);

// PARSER
void parser_map(t_game *game, char *file);
char **ft_read_file(char *file);

// ERRORS HANDLERS
void	ft_validate_error(char *error_msg);
void	ft_parser_error(char *error_msg, t_game *game);

// FREE
void	ft_free_game(t_game *game);



#endif
