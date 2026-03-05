/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:35 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/05 12:19:15 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	"libft.h"
# include	<math.h> 
# include	"../MLX42/include/MLX42/MLX42.h"

typedef struct s_img
{
	mlx_image_t	*img;
	uint8_t		*addr;//puntero al array de bytes de la imagen
} t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
} t_player;

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
	int		no_set;
	int		so_set;
	int		we_set;
	int		ea_set;
	int		floor_set;
	int		ceiling_set;
}	t_config;

typedef struct s_game
{
	t_map*		map;
	t_config	config_map;
	t_player	player;
	t_img		frame;
	mlx_t		*mlx;
	int			win_w;
	int			win_h;
}	t_game;

// VALIDATION
void	ft_validate_args(int ac, char **av);
int		ft_openfd(char *file);

// PARSER
void	parser_map(t_game *game, char *file);
char	**ft_read_file(char *file);
void	ft_parse_file(t_game *game, char **lines);
void	ft_parse_config_line(t_game *game, char *line);
void	ft_parse_map(t_game *game, char **lines, int start);

// UTILS PARSER
char	*ft_skip_spaces(char *str);
int		ft_is_map_line(char *line);

// ERRORS HANDLERS
void	ft_validate_error(char *error_msg);
void	ft_parser_error(char *error_msg, t_game *game);

// VALIDATION helpers
void	validate_render_contract(t_game *game);
void	ft_validate_config(t_game *game);
void	ft_validate_map(t_game *game);

// FREE
void	ft_free_game(t_game *game);
void	ft_free_split(char **split);
void	free_partial_map(char **map, int filled);

// INIT GAME
void	init_game(t_game *game);
void	init_mlx(t_game *game);
void	start_game(t_game *game);
void	init_player(t_game *game);

// RENDER
void	render_base(t_game *game);

#endif
