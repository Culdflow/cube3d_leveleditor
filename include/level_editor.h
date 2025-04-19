/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:07:34 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/19 02:19:49 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVEL_EDITOR_H
# define LEVEL_EDITOR_H
# include "../lib/minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "utils.h"
# include "../lib/libft/libft.h"

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_vector2	pos;
	t_vector2	size;
}	t_img;

typedef struct s_moves
{
	t_vector2		pos;
	struct s_moves	*next;
}	t_moves;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_object_list	*obj_list;
	char			**board;
	int				is_clicking;
	t_vector2		board_size;
	char			turning_to;
	t_img			imgs[50000];
}	t_mlx;

////////////////////////---RENDER---//////////////////////////////////////////

void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		draw_rectangle(t_img *data, t_vector2 start, t_vector2 end, int color);
void		draw_board(t_mlx *mlx, int	color1, char **board, t_vector2 board_size);
void		draw_rectangle_no_fill(t_img *data, t_vector2 start, t_vector2 end, int color);
void		draw_object_list(t_mlx *mlx, t_object_list *obj_lst);

////////////////////////---IMAGES---//////////////////////////////////////////

void		del_images(t_mlx *mlx);
void		add_image(t_mlx *mlx, t_img img);
int			count_images(t_mlx *mlx);
void		put_imgs(t_mlx *mlx);
int			xpm_file_to_img(t_mlx *mlx, char *path, t_vector2 pos);
int			new_image(t_mlx *mlx, t_vector2 size, t_vector2 pos);
void		put_img_to_img(t_img *dst, t_img src, int x, int y);
t_vector2	get_pos_mouse(t_mlx *mlx);

#endif