/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:24:25 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/03/03 12:41:08 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char *ft_skip_spaces(char *str)
{
	while (ft_is_space(*str))
		str++;
	return str;
}

int	ft_is_map_line(char *line)
{
	char *p;

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
