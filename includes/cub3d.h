/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:59:35 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/10 11:00:30 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>

# define MOVE_SPEED 0.06
# define ROT_SPEED 0.04
# define PLAYER_RADIUS 0.15
# define MIN_PERP_DIST 0.65	

typedef struct s_map
{
	char **map;
	int	map_width;
	int	map_height;
}	t_map;

typedef struct s_img
{
	mlx_image_t	*img;
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

typedef struct s_config
{
	char			*tex_no;
	char			*tex_so;
	char			*tex_we;
	char			*tex_ea;
	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_we;
	mlx_texture_t	*texture_ea;
	int				floor_color[3];
	int				ceiling_color[3];
	int				floor_set;
	int				ceiling_set;
	int				no_set;
	int				so_set;
	int				we_set;
	int				ea_set;
}	t_config;

typedef struct s_game
{
	t_map*			map;
	t_config		config_map;
	t_player		player;
	t_img			frame;
	mlx_t			*mlx;
	int				win_w;
	int				win_h;
}	t_game;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

// VALIDATION
void	ft_validate_args(int ac, char **av);

// PARSER
void	parser_map(t_game *game, char *file);
char	**ft_read_file(char *file);
void	ft_parse_file(t_game *game, char **lines);
void	ft_validate_game(t_game *game);
void	ft_free_split(char **split);
void	validate_render_contract(t_game *game);

// PARSER HELPERS
char	*ft_skip_spaces(char *str);
int		ft_is_map_line(char *line);
int		ft_valid_map_char(char c);
int		ft_str_isdigits(char *str);
char	*ft_strtrim_newline(char *str);
void	free_partial_map(char **map, int height);
void	ft_parse_config_line(t_game *game, char *line);
void	ft_parse_map(t_game *game, char **lines, int start);

// PARSER VALIDATION
void	ft_validate_config(t_game *game);
void	ft_validate_map(t_game *game);
void	ft_validate_map_chars(t_game *game);
void	ft_validate_player(t_game *game);

// ERRORS HANDLERS
void	ft_validate_error(char *error_msg);
void	ft_parser_error(char *error_msg, t_game *game);

// FREE
void	ft_free_game(t_game *game);

// INIT GAME
void	init_game(t_game *game);
void	init_mlx(t_game *game);
void	start_game(t_game *game);
void	init_player(t_game *game);
void	load_textures(t_game *game);

// RENDER
void	render_base(t_game *game);

// MOVE PLAYER
void	move_player(t_game *game);

// RAYCASTING
void	render_walls(t_game *game);
void	init_dda_step(t_game *game, double ray_dir_x, double ray_dir_y,
        t_dda *dda);
int		is_wall_cell(t_game *game, int map_x, int map_y);
double	compute_perp_dist(t_game *game, t_dda *dda,
		double ray_dir_x, double ray_dir_y);
void	draw_texture(t_game *game, int x, t_dda *dda, int limits[2],
		double ray_dir[2], double perp_dist);

// TEXTURES
uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y);

#endif
