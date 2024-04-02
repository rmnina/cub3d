/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:49:26 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/02 12:41:49 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_player_pos(t_data *data, char c, int y, int x)
{
	if (data->player->orient)
		return (PARSING_ERROR);
	data->player->orient = c;
	data->player->pos_x = x;
	data->player->pos_y = y;
	return (SUCCESS);
}

// checks if the line contains only 1, 0, whitespaces or player pos. 
// if the player pos is encountered, it is stored within the t_player struct.
// the N/S/W/E char is the orientation; the i (navigates through one line) 
// is the x (abscissa) (position; the y (i from next function, 
// navigates through all lines) would be the position on the ordinate axis.

int	ft_valid_map_line(t_data *data, char **line, int y)
{
	int		i;

	i = 0;
	while ((*line) && (*line)[i])
	{
		if (ft_is_player_pos((*line)[i]))
		{
			if (get_player_pos(data, (*line)[i], y, i))
				return (0);
			(*line)[i] = '0';
		}
		else if ((*line)[i] != '0' && (*line)[i] != '1' \
		&& !ft_isspace((*line)[i]))
			return (0);
		i++;
	}
	return (1);
}

int	store_map(t_data *data)
{
	int	height;
	int	length;
	int	valid;

	height = 0;
	length = 0;
	data->map->map_tab[0] = NULL;
	valid = ft_valid_map_line(data, &data->map->line, height);
	while (data->map->line && valid && !ft_is_empty_line(data->map->line))
	{
		data->map->map_tab = ft_strjoin_map(data->map->map_tab, \
		data->map->line);
		if (!data->map->map_tab)
			return (strerror(ENOMEM), UNKNOWN_ERROR);
		length = ft_strlen(data->map->line);
		if (length > data->map->map_width)
			data->map->map_width = length;
		height++;
		data->map->line = get_next_line(data->map->fd);
		valid = ft_valid_map_line(data, &data->map->line, height);
		if (!valid)
			return (PARSING_ERROR);
	}
	data->map->map_height = height;
	return (SUCCESS);
}

int	finish_gnl(t_data *data)
{
	int	error;

	error = 0;
	if (!data->map->line)
		data->map->line = get_next_line(data->map->fd);
	while (data->map->line)
	{
		if (data->map->line && !ft_is_empty_line(data->map->line))
			error = 1;
		free(data->map->line);
		data->map->line = get_next_line(data->map->fd);
	}
	free(data->map->line);
	data->map->line = NULL;
	return (error);
}

int	parse_map(t_data *data)
{
	data->map->line = get_next_line(data->map->fd);
	while (data->map->line && ft_is_empty_line(data->map->line))
	{
		free(data->map->line);
		data->map->line = get_next_line(data->map->fd);
	}
	if (!ft_is_empty_line(data->map->line) && \
	!ft_valid_map_line(data, &data->map->line, 0))
		return (PARSING_ERROR);
	if (!data->map->line)
		return (PARSING_ERROR);
	data->map->map_tab = malloc(sizeof(char *));
	if (!data->map->map_tab)
		return (strerror(ENOMEM), UNKNOWN_ERROR);
	if (store_map(data))
		return (PARSING_ERROR);
	if (data->player->pos_x == -1 || data->player->pos_y == -1 \
	|| !data->player->orient)
		return (PARSING_ERROR);
	if (data->map->line)
	{
		if (finish_gnl(data))
			return (PARSING_ERROR);
	}
	return (SUCCESS);
}
