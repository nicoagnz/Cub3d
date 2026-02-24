/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacuna-g <nacuna-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 11:17:15 by nacuna-g          #+#    #+#             */
/*   Updated: 2026/02/24 12:06:23 by nacuna-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int count_lines(char *file)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char **ft_read_file(char *file)
{
	int fd;
	char *line;
	char **lines;
	int i;
	int total_lines;

	total_lines = count_lines(file);
	if (total_lines <= 0)
		ft_parser_error_handler("Empty or invalid file", NULL);
	lines = malloc(sizeof(char *) * (total_lines + 1));
	if (!lines)
		ft_parser_error_handler("Malloc failed", NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		ft_parser_error_handler("Could not open file", NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)))
		lines[i++] = line;
	lines[i] = NULL;
	close(fd);
	return (lines);
}
