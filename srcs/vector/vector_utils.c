/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 20:19:52 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 02:29:16 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/level_editor.h"

int	clamp(int *nb, int min, int max)
{
	if (min > max)
		return (0);
	if (*nb < min)
	{
		*nb = min;
		return (-1);
	}
	else if (*nb > max)
	{
		*nb = max;
		return (-1);
	}
	return (0);
}

t_vector2	mul_vec2(t_vector2 vec1, t_vector2 vec2)//Returns vec1 * vec2
{
	t_vector2	result;

	result.x = vec1.x * vec2.x;
	result.y = vec1.y * vec2.y;
	return (result);
}

int	clamp_vec2(t_vector2 *vec, t_vector2 min, t_vector2 max)
{
	int	is_invalid;

	is_invalid = 0;
	if (clamp(&vec->x, min.x, max.x) < 0)
		is_invalid = -1;
	if (clamp(&vec->y, min.y, max.y) < 0)
		is_invalid = -1;
	if (is_invalid < 0)
		return (-1);
	return (0);
}

int	compare_vec2(t_vector2 vec1, t_vector2 vec2)
{
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}

t_vector2	vec2_inv_x(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y;
	result.x = vec.x * -1;
	return (result);
}

t_vector2	vec2_inv_y(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y * -1;
	result.x = vec.x;
	return (result);
}

t_vector2	vec2_inv(t_vector2 vec)
{
	t_vector2	result;

	result.y = vec.y * -1;
	result.x = vec.x * -1;
	return (result);
}

int	reverse_bool(int a)
{
	if (a == 0 || a == -1)
		return (1);
	else
		return (0);
}

int	check_vector_in_zone(t_vector2 mouse_pos, t_vector2 zone_start, t_vector2 zone_end)
{
	zone_start = vec2_make_start(zone_start, zone_end);
	zone_end = vec2_make_end(zone_start, zone_end);
	if (mouse_pos.x >= zone_start.x && mouse_pos.x <= zone_end.x
			&& mouse_pos.y >= zone_start.y && mouse_pos.y <= zone_end.y)
			return (TRUE);
	return (FALSE);
}