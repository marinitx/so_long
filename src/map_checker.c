/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:53:03 by mhiguera          #+#    #+#             */
/*   Updated: 2023/12/22 20:12:07 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"
#include <stdio.h>

void	check_different(t_map *map, t_game *game)
{
	int	row;
	int	col;

	row = 0;
	game = &map->game;
	col = 0;
	while (map->map[row][col] != '\0' && row < map->height)
	{
		col = 0;
		while (map->map[row][col] != '\n')
		{
			if ((map->map[row][col] != '0' && map->map[row][col] != '1') &&
				(map->map[row][col] != 'C') &&
				(map->map[row][col] != 'E' && map->map[row][col] != 'P') &&
				(map->map[row][col] != '\n' && map->map[row][col] != '\0'))
				ft_error("Error\nWrong characters on the map!\n");
			col++;
		}
		row++;
	}
	flood_fill_from_player(map, game->player_y, game->player_x);
}

void	check_char2(t_map *map, t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (map->map[row][col] != '\0' && row < map->height)
	{
		col = 0;
		while (map->map[row][col] != '\n')
		{
			if (map->map[row][col] == 'P')
			{
				game->player_y = row;
				game->player_x = col;
				game->player_count++;
			}
			if (map->map[row][col] == 'C')
				game->all_coins++;
			col++;
		}
		row++;
	}
	game->coins = game->all_coins;
	map->coins_copy = game->all_coins;
}

//DIVIDIR EN 2
void	check_char(t_map *map, t_game *game)
{
	int	row;
	int	col;

	game = &map->game;
	row = 0;
	col = 0;
	while (map->map[row][col] != '\0' && row < map->height)
	{
		col = 0;
		while (map->map[row][col] != '\n')
		{
			if (map->map[row][col] == 'E')
			{
				game->exit_count++;
				game->exit_row = row;
				game->exit_col = col;
			}
			col++;
		}
		row++;
	}
	check_char2(map, game);
	if (game->player_count != 1 || game->exit_count != 1)
		ft_error("Error\nMap not valid\n");
}

void	check_borders2(t_map *map, int row, int col)
{
	row = 0;
	col = 0;
	while (map->map[row][col] != '\0')
	{
		if (row == map->height - 1)
		{
			while (map->map[row][col] != '\0')
			{
				if (map->map[0][col] != '1'
					|| map->map[map->height - 1][col] != '1')
					ft_error("Error\nMap is not surrounded by walls!\n");
				col++;
			}
		}
		if ((row > 0) && (row < map->height - 1))
		{
			if (map->map[row][0] != '1' || map->map[row][map->width - 1] != '1')
				ft_error("Error\nMap is not surrounded by walls!\n");
			col++;
		}
		if (row < map->height - 1)
			row++;
	}
}

void	map_checker(t_map *map)
{
	t_game	game;

	game.all_coins = 0;
	game.exit_count = 0;
	game.player_count = 0;
	game.movements = 0;
	map->game = game;
	check_width(map);
	check_borders(map);
	check_char(map, &game);
	check_different(map, &game);
	check_path(map);
	ft_init(map);
}
