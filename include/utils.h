/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:33:25 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 18:19:55 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <string.h>

# define K_A 97
# define K_B 98
# define K_C 99
# define K_D 100
# define K_E 101
# define K_F 102
# define K_G 103
# define K_H 104
# define K_I 105
# define K_J 106
# define K_K 107
# define K_L 108
# define K_M 109
# define K_N 110
# define K_O 111
# define K_P 112
# define K_Q 113
# define K_R 114
# define K_S 115
# define K_T 116
# define K_U 117
# define K_V 118
# define K_W 119
# define K_X 120
# define K_Y 121
# define K_Z 122
# define K_AR_L 65361
# define K_AR_R 65363
# define K_AR_U 65362
# define K_AR_D 65364
# define K_NP_DIV 65455
# define K_NP_MUL 65450
# define K_NP_MIN 65453
# define K_NP_PLU 65451
# define K_SP 32
# define K_ESC 65307
# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5

enum e_event//Events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef enum e_object_type
{
	BUTTON = 1,
	LABEL = 2
}	object_type;

typedef struct s_vector2
{
	int	x;
	int	y;
}	t_vector2;

typedef struct s_object
{
	object_type		type;
	t_vector2		pos;
	t_vector2		size;
	char			*tag;
	int				value;
	int				color;
	void			(*clickFunc)(void *, int);
	void			*victim;
}	t_object;

typedef struct s_object_list
{
	t_object				*object;
	struct s_object_list	*next;
}	t_object_list;

////////////////////////---VECTOR---//////////////////////////////////////////

t_vector2		vec2(int x, int y);
t_vector2		vec2_make_start(t_vector2 start, t_vector2 end);
t_vector2		vec2_make_end(t_vector2 start, t_vector2 end);
int				compare_vec2(t_vector2 vec1, t_vector2 vec2);
t_vector2		add_vec2(t_vector2 vec1, t_vector2 vec2);
t_vector2		sub_vec2(t_vector2 vec1, t_vector2 vec2);
t_vector2		mul_vec2(t_vector2 vec1, t_vector2 vec2);
int				clamp_vec2(t_vector2 *vec, t_vector2 min, t_vector2 max);
t_vector2		vec2_inv_x(t_vector2 vec);
t_vector2		vec2_inv_y(t_vector2 vec);
t_vector2		vec2_inv(t_vector2 vec);
int				abs(int x);
int				check_vector_in_zone(t_vector2 mouse_pos, t_vector2 zone_start, t_vector2 zone_end);
t_vector2		div_vec2(t_vector2 vec1, t_vector2 divi);


void			check_if_obj_clicked(t_vector2 mouse_pos, t_object_list *lst);
void			add_obj_to_list(t_object_list **lst, t_object *obj);
t_object		*create_obj(int type, void (*onClick)(void *, int), int value, t_vector2 pos, t_vector2 size, int color, char *tag, void *victim);
t_object_list	*get_last_object(t_object_list *start);
void			free_object_list(t_object_list *start);
void			board_clicked(t_vector2 mouse_pos, t_vector2 board_size, char **board);

void			free_tab(char **tab, t_vector2 tab_size);

#endif