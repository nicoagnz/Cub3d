/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:24:25 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/16 12:44:20 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

char	*ft_skip_spaces(char *str)
{
	while (ft_is_space(*str))
		str++;
	return (str);
}

int	ft_is_map_line(char *line)
{
	char	*p;

	p = line;
	if (!p || *p == '\0')
		return (0);
	while (*p)
	{
		if (*p != '0' && *p != '1'
			&& *p != 'N' && *p != 'S'
			&& *p != 'E' && *p != 'W'
			&& *p != ' ' && *p != '\t')
			return (0);
		p++;
	}
	return (1);
}

int	ft_valid_map_char(char c)
{
	if (c == '0' || c == '1'
		|| c == ' '
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}
