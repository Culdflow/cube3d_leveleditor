/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:12 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 18:27:56 by dfeve            ###   ########.fr       */
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
		new_image(mlx, vec2(300, 300), vec2(0, 0));
		put_imgs(mlx);
		draw_object_list(mlx, mlx->obj_list);
	}
	return (1);
}

int	_input_mouse_board(int keycode, int x, int y, t_mlx *mlx)
{
	t_vector2	pos;

	pos.x = x;
	pos.y = y;
	if (keycode == M_CLK_L)
	{
		check_if_obj_clicked(pos, mlx->obj_list);
		del_images(mlx);
		board_clicked(pos, mlx->board_size, mlx->board);
		new_image(mlx, vec2(1920, 1080), vec2(0, 0));
		draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
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

void	mlx_loop_end_signal(void *vmlx, int new_value)
{
	(void)new_value;
	t_mlx	*mlx;
	mlx = (t_mlx *)vmlx;
	mlx_loop_end(mlx->mlx);
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
	t_object	*label_x;
	t_object	*label_y;
	char		*name;

	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 300, 300, "SELECT SIZE");
	mlx->imgs[0].img = NULL;
	mlx->obj_list = NULL;
	label_x = create_obj(LABEL, NULL, 10, vec2(50, 100), vec2(25, 25), 0xFFFFFF, "X VALUE", NULL);
	label_y = create_obj(LABEL, NULL, 10, vec2(100, 100), vec2(25, 25), 0xFFFFFF, "Y VALUE", NULL);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 1, vec2(50, 65), vec2(25, 15), 0xFFFFFF, "", label_x));
	add_obj_to_list(&mlx->obj_list, label_x);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 2, vec2(50, 120), vec2(25, 15), 0xFFFFFF, "", label_x));
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_up, 3, vec2(100, 65), vec2(25, 15), 0xFFFFFF, "", label_y));
	add_obj_to_list(&mlx->obj_list, label_y);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, modif_label_down, 4, vec2(100, 120), vec2(25, 15), 0xFFFFFF, "", label_y));
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, mlx_loop_end_signal, 5, vec2(150, 90), vec2(25, 15), 0xFFFFFF, "CREATE", mlx));
	printf("%d\n", new_image(mlx, vec2(300, 300), vec2(0, 0)));
	draw_object_list(mlx, mlx->obj_list);
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_mouse_hook(mlx->win, _input_mouse, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, mlx_loop_end, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	mlx->board_size = vec2(label_x->value, label_y->value);
	free_object_list(mlx->obj_list);
	del_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
//////////////////////////////////////////////////////////////////////////////
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "EDIT MAP");
	mlx->imgs[0].img = NULL;
	mlx->obj_list = NULL;
	mlx->board = create_board(mlx->board_size);
	new_image(mlx, vec2(1920, 1080), vec2(0, 0));
	draw_board(mlx, 0xFFFFFF, mlx->board, mlx->board_size);
	add_obj_to_list(&mlx->obj_list, create_obj(BUTTON, mlx_loop_end_signal, 5, vec2(1750, 450), vec2(50, 25), 0xFFFFFF, "SUBMIT", mlx));
	mlx_hook(mlx->win, ON_KEYDOWN, 1L << 0, _input, mlx);
	mlx_mouse_hook(mlx->win, _input_mouse_board, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0, mlx_loop_end, mlx->mlx);
	put_imgs(mlx);
	draw_object_list(mlx, mlx->obj_list);
	mlx_loop(mlx->mlx);
	free_object_list(mlx->obj_list);
	del_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	int			fd;
	char		*tmp;
	t_vector2	cursor;

	name = readline("Name the file: ");
	cursor = vec2(0, 0);
	tmp = ft_strjoin(name, ".cub");
	free(name);
	name = tmp;
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (cursor.y < mlx->board_size.y)
	{
		cursor.x = 0;
		while (cursor.x < mlx->board_size.x)
		{
			write(fd, &mlx->board[cursor.y][cursor.x], 1);
			cursor.x++;
		}
		write(fd, "\n", 1);
		cursor.y++;
	}
	close(fd);
	free_tab(mlx->board, mlx->board_size);
	free(mlx->mlx);
	free(mlx);
}
