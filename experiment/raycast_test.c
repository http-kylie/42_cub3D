/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:42:45 by kecheong          #+#    #+#             */
/*   Updated: 2024/10/23 11:46:07 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>

typedef struct s_box
{
	float	centerX;
	float	centerY;
	float	halfDimension;
}	t_box;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_box	player;
}	t_mlx;

#define L_ENDIAN 0
#define B_ENDIAN 1

/* pixel[0] = r
 * pixel[1] = g
 * pixel[2] = b
 * pixel[3] = t */
void*	createBoxImage(t_mlx *game)
{
	void	*img = mlx_new_image(game->mlx, 64, 64);
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			int	pixel = (y * size_line) + (x * 4);
			addr[pixel] = 0xFF;
			addr[pixel + 1] = 0xFF;
			addr[pixel + 2] = 0xFF;
			addr[pixel + 3] = 0x00;
		}
	}
	return img;
}

void*	createPlayerImage(t_mlx *game)
{
	void	*img = mlx_new_image(game->mlx, 64, 64);
	int		bpp, size_line, endian;
	char	*addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	for (int y = 0; y < 64; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			int	pixel = (y * size_line) + (x * 4);
			addr[pixel] = 0xFF;
			addr[pixel + 1] = 0xF3;
			addr[pixel + 2] = 0x38;
			addr[pixel + 3] = 0x00;
		}
	}
	return img;
}

int	createColor(t_mlx *game, int r, int g, int b, int t)
{
	static int endian = -1;
	if (endian == -1) // TODO: for checking endianness
	{
		void	*tmp_img = mlx_new_image(game->mlx, 1, 1);
		int		temp;
		mlx_get_data_addr(tmp_img, &temp, &temp, &endian);
	}
	return (t << 24 | r << 16 | g << 8 | b);
}

#define WIDTH 7
#define HEIGHT 7
const char	map[HEIGHT][WIDTH] = {
{'1', '1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', 'P', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '1'},
{'1', '0', '0', '0', '0', '0', '1'},
{'1', '1', '1', '1', '1', '1', '1'}
};

int	render(t_mlx *game)
{
	void	*box_img = createBoxImage(game);
	void	*player_img = createPlayerImage(game);
	t_box	box = {0};
	int		y = 32;
	int loop = 0; (void)loop;
	for (int i = 0; i < HEIGHT; i++)
	{
		int	x = 32;
		for (int j = 0; j < WIDTH; j++)
		{
			box.centerX = x;
			box.centerY = y;
			box.halfDimension = 32;
			if (map[i][j] == '1')
			{
				mlx_put_image_to_window(game->mlx, game->window, box_img,
							   box.centerX - box.halfDimension,
							   box.centerY - box.halfDimension);
			}
			else if (map[i][j] == 'P')
			{
				mlx_put_image_to_window(game->mlx, game->window, player_img,
								game->player.centerX - box.halfDimension,
								game->player.centerY - box.halfDimension);
			}
			x += 64;
		}
		y += 64;
	}
	return 0;
}

int		game_loop(t_mlx *game)
{
	mlx_clear_window(game->mlx, game->window);
	render(game);
	return 0;
}

enum	e_keys
{
	KEY_LEFT = 0,
	KEY_DOWN = 1,
	KEY_RIGHT = 2,
	KEY_UP = 13,
	KEY_ESC = 53
};

int	process_key_press(int keycode, t_mlx *game)
{
	if (keycode == KEY_LEFT)
	{
		game->player.centerX -= 5;
	}
	else if (keycode == KEY_DOWN)
	{
		game->player.centerY += 5;
	}
	else if (keycode == KEY_RIGHT)
	{
		game->player.centerX += 5;
	}
	else if (keycode == KEY_UP)
	{
		game->player.centerY -= 5;
	}
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	return 0;
}

int	main(void)
{
	t_mlx	game;
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WIDTH * 64, HEIGHT * 64, "Hello World");
	game.player = (t_box){.centerX = 224.0f, .centerY = 228.0f, .halfDimension = 32.0f};

	mlx_hook(game.window, 2, 0, process_key_press, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(&game);
}

