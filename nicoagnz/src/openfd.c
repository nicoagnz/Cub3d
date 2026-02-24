/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:32:08 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/23 11:16:24 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_openfd(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}
