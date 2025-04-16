/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 02:26:05 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

int	_input(int keycode, t_mlx *mlx)
{
	if (keycode == K_ESC)
		mlx_loop_end(mlx->mlx);
	return (1);
}

int	_input_mouse(int keycode, int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	pos.x = x;
	pos.y = y;
	if (keycode == M_CLK_L)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		del_images(mlx);
		new_image(mlx, vec2(400, 400), vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

void	modif_label_up(void *obj_lst, int new_value)
{
	(void)new_value;
	t_object *newobj_lst;
	newobj_lst = (t_object *)obj_lst;
	newobj_lst->value = newobj_lst->value + 1;
}

void	modif_label_down(void *obj_lst, int new_value)
{
	(void)new_value;
	t_object *newobj_lst;
	newobj_lst = (t_object *)obj_lst;
	newobj_lst->value = newobj_lst->value - 1;
}

char	**create_board(t_vector2 size)
{
	char		**result;
	t_vector2	cursor;

	cursor = vec2(0, 0);
	result = malloc(sizeof(char *) * (size.y + 1));
	result[size.y] = 0;
	while (cursor.y < size.y)
	{
		cursor.x = 0;
		result[cursor.y] = malloc(sizeof(char) * (size.x + 1));
		while (cursor.x < size.x)
		{
			result[cursor.y][cursor.x] = '0';
			cursor.x++;
		}
		result[cursor.y][cursor.x] = 0;
		cursor.y++;
	}
	return (result);
}

int	main()
{
	t_mlx		*mlx;
	char		**board;
	// t_object	*label_x;
	// t_object	*label_y;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "SELECT SIZE");
	mlx->imgs[0].img = NULL;
	mlx->obj_list = NULL;
	// label_x = create_obj(LABEL, NULL, 5, vec2(50, 100), vec2(25, 25), 0xFFFFFF, "X VALUE", NULL);
	// label_y = create_obj(LABEL, NULL, 5, vec2(100, 100), vec2(25, 25), 0xFFFFFF, "Y VALUE", NULL);
	// add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 1, vec2(50, 65), vec2(25, 15), 0xFFFFFF, "", label_x));
	// add_obj_to_list(&mlx->obj_list, label_x);
	// add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 1, vec2(50, 120), vec2(25, 15), 0xFFFFFF, "", label_x));
	// add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 1, vec2(100, 65), vec2(25, 15), 0xFFFFFF, "", label_y));
	// add_obj_to_list(&mlx->obj_list, label_y);
	// add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 1, vec2(100, 120), vec2(25, 15), 0xFFFFFF, "", label_y));
	// add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 1, vec2(150, 90), vec2(25, 15), 0xFFFFFF, "CREATE", NULL));
	new_image(mlx, vec2(1920, 1080), vec2(0, 0));
	board = create_board(vec2(30, 30));
	board[0][1] = '1';
	draw_board(mlx, 0xFFFFFF, board, vec2(30, 30));
	// draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_mouse_hook(mlx->win, _input_mouse, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, mlx_loop_end, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	free_object_list(mlx->obj_list);
	del_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}
