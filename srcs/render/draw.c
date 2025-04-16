/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:16:16 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 17:38:05 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/level_editor.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	if (color != 0xe29c9c)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	t_vector2	cursor;
	t_vector2	goal;
	int			x;

	if (!data)
		return ;
	clamp_vec2(&start, vec2(0, 0), vec2(1920, 1080));
	clamp_vec2(&end, vec2(0, 0), vec2(1920, 1080));
	cursor = vec2_make_start(start, end);
	x = cursor.x;
	goal = vec2_make_end(start, end);
	while (cursor.y <= goal.y)
	{
		cursor.x = x;
		while (cursor.x <= goal.x)
		{
			my_mlx_pixel_put(data, cursor.x, cursor.y, color);
			cursor.x++;
		}
		cursor.y++;
	}
}

void	draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end, int color)
{
	int	i;

	i = start.x;
	while (i <= end.x)
	{
		my_mlx_pixel_put(data, i, start.y, color);
		my_mlx_pixel_put(data, i++ , end.y, color);
	}
	i = start.y;
	while (i <= end.y)
	{
		my_mlx_pixel_put(data, start.x, i, color);
		my_mlx_pixel_put(data, end.x , i++, color);
	}
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) + (x * img.bits_per_pixel / 8))));
}

void	put_img_to_img(t_img *dst, t_img src, int x, int y)
{
	int i;
	int j;

	i = 0;
	while(i < src.size.y)
	{
		j = 0;
		while (j < src.size.x) {
			my_mlx_pixel_put(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

void	draw_board(t_mlx *mlx, int	color1, char **board, t_vector2 board_size)
{
	t_vector2	cursor;
	t_vector2	screen_size;
	t_vector2	start;
	t_vector2	end;

	screen_size = vec2(1500, 900);
	cursor = vec2(0, 0);
	while (cursor.y < board_size.y)
	{
		cursor.x = 0;
		while (cursor.x < board_size.x)
		{
			start = mul_vec2(cursor, div_vec2(screen_size, board_size));
			end = mul_vec2(add_vec2(cursor, vec2(1, 1)), div_vec2(screen_size, board_size));
			if (board[cursor.y][cursor.x] == '0')
				draw_rectangle_no_fill(&mlx->imgs[0], add_vec2(start, vec2(20, 20)), add_vec2(end, vec2(20, 20)), color1);
			else if (board[cursor.y][cursor.x] == '1')
				draw_rectangle(&mlx->imgs[0], add_vec2(start, vec2(20, 20)), add_vec2(end, vec2(20, 20)), color1);
			cursor.x++;
		}
		cursor.y++;
	}
}

void	draw_object(t_mlx *mlx, t_object *obj)
{
	char *string;

	string = NULL;
	if (obj->type == BUTTON)
	{
		draw_rectangle(&mlx->imgs[0], obj->pos, add_vec2(obj->pos, obj->size), obj->color);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x, obj->pos.y - 10, 0xFF0000, obj->tag);
	}
	else if (obj->type == LABEL)
	{
		string = ft_itoa(obj->value);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x , obj->pos.y, obj->color, obj->tag);
		mlx_string_put(mlx->mlx, mlx->win, obj->pos.x + 10 , obj->pos.y + 15, obj->color, string);
		free(string);
	}
}

void	draw_object_list(t_mlx *mlx, t_object_list *obj_lst)
{
	while (obj_lst)
	{
		printf("drawing object wth value %d\n", obj_lst->object->value);
		draw_object(mlx, obj_lst->object);
		obj_lst = obj_lst->next;
	}
}
