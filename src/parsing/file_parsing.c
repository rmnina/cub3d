/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:27:28 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/26 13:47:20 by tsaint-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// split with ',' ? check if 3 componoents + atoi + bitshift
// implement error messages

int	rgb_to_int(char *rgb)
{
	char	**split_rgb;
	int		cpt;
	int		res;
	
	if (!rgb)
		return (-1);
	split_rgb = ft_split(rgb, ',');
	if (!split_rgb)
		return (free(rgb), free_dchartab(split_rgb), -1);
	cpt = 0;
	while (split_rgb[cpt])
		cpt++;
	if (cpt != 3)
		return (free(rgb), free_dchartab(split_rgb), -1);
	cpt = 0;
	res = 0;
	while (split_rgb[cpt])
	{
		if (!ft_isnum(split_rgb[cpt]))
			return (free(rgb), free_dchartab(split_rgb), -1);
		res = (res << 8) + ft_atoi(split_rgb[cpt++]);
	}
	free_dchartab(split_rgb);
	free(rgb);
	return (res);
}

//protect strtrim !!
int	fill_element(t_data *data, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		return (0);
	if (!ft_strncmp(line, "NO", 2))
		data->map->walls[NORTH] = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "SO", 2))
		data->map->walls[SOUTH] = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "WE", 2))
		data->map->walls[WEST] = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "EA", 2))
		data->map->walls[EAST] = ft_strtrim(line + 2, " \t\n\v\r");
	else if (!ft_strncmp(line, "F", 1))
		data->map->floor = rgb_to_int(ft_strtrim(line + 1, " \t\n\v\r"));
	else if (!ft_strncmp(line, "C", 1))
		data->map->floor = rgb_to_int(ft_strtrim(line + 1, " \t\n\v\r"));
	else
		return (0);
	return (1);
}

int	parse_elements(t_data *data)
{
	char	*line;
	int		nb_elem;
	int		filled;

	nb_elem = 0;
	filled = 0;
	line = get_next_line(data->map->fd);
	while (line && nb_elem < 6)
	{
		filled = fill_element(data, line);
		if (filled == -1)
			return (PARSING_ERROR);
		else if (filled)
			nb_elem++;
		free(line);
		line = get_next_line(data->map->fd);
	}
	return (SUCCESS);
}

// way too long and messy, just a first try on how to structure the parsing
// for now it only assigns the NO SO WE EA textures to the struct

int	file_parsing(t_data *data)
{
	if (parse_elements(data))
		return (PARSING_ERROR);
	// if (parse_map(data));
	// 	return (PARSING_ERROR);
	return (SUCCESS);
}