/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:28:02 by tsaint-p          #+#    #+#             */
/*   Updated: 2024/03/26 19:41:35 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->file_path = NULL;
	map->map_tab = NULL;
	map->walls[NORTH] = NULL;
	map->walls[SOUTH] = NULL;
	map->walls[WEST] = NULL;
	map->walls[EAST] = NULL;
	map->ceiling = 0;
	map->floor = 0;
	map->fd = 0;
	map->map_height = 0;
	map->map_width = 0;
	return (map);
}

t_player	*init_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->orient = 0;
	player->pos_x = -1;
	player->pos_y = -1;
	return (player);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map = init_map();
	if (!data->map)
		return (free(data), NULL);
	data->player = init_player();
	if (!data->player)
		return (free(data->map), free(data), NULL);
	return (data);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	clean_exit(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
	{
		ft_free(data->map->file_path);
		ft_free(data->map->file_path); //never changed before
		ft_free(data->map->walls[0]);
		ft_free(data->map->walls[1]);
		ft_free(data->map->walls[2]);
		ft_free(data->map->walls[3]);
		if (data->map->fd > 0)
			close(data->map->fd);
		ft_free(data->map);
	}
	free(data);
}

void	print_player(t_player *player)
{
	printf("player->orient = %c\n", player->orient);
	printf("player->pos_x = %d\n", player->pos_x);
	printf("player->pos_y = %d\n", player->pos_y);
}

void	print_map(t_map *map)
{
	printf("map : %p\n", map);
	printf("map->file_path = %s\n", map->file_path);
	printf("map->fd = %d\n", map->fd);
	printf("map->walls[0] = %s\n", map->walls[0]);
	printf("map->walls[1] = %s\n", map->walls[1]);
	printf("map->walls[2] = %s\n", map->walls[2]);
	printf("map->walls[3] = %s\n", map->walls[3]);
	printf("map->ceiling = %x\n", map->ceiling);
	printf("map->floor = %x\n", map->floor);
	printf("map->height = %d\n", map->map_height);
	printf("map->width = %d\n", map->map_width);
	printf("map->map_tab = \n");
	for (int i = 0; map->map_tab[i]; i++)
	{
		printf("%s", map->map_tab[i]);
	}
}

void	help(void)
{
	printf("Cub3d program usage:\n");
	printf("  ./cub3D file_path.cub\n\n");
	printf("The file.cub should contain the following mandatory elements:\n");
	printf("  - NO north_texture_path (Example: NO ./path_to_the_north_texture)\n");
	printf("  - SO south_texture_path\n");
	printf("  - WE west_texture_path\n");
	printf("  - EA east_texture_path\n");
	printf("  - F XXX,XXX,XXX (RGB format, for the Floor)\n");
	printf("  - C XXX,XXX,XXX (RGB format, for the Ceiling)\n");
	printf("  - A map\n\n");
	printf("The map must fulfill the following specifications:\n");
	printf("  - The map must be composed of only 6 possible characters: \n");
	printf("    • 0 for an empty space\n    • 1 for a wall\n");
	printf("    • N, S, E, or W for the player’s start position and orientation.\n");
	printf("  - The map must be closed/surrounded by walls.\n");
	printf("  - The map content always has to be the last element of the file.\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	data = init_data();
	if (!data)
		return (-1);
	parsing(argc, argv, data);
	// print_map(data->map);
	// print_player(data->player);
	clean_exit(data);
	return (0);
}
