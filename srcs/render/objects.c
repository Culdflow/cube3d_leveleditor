/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <dfeve@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:10:15 by dfeve             #+#    #+#             */
/*   Updated: 2025/04/16 02:29:13 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/level_editor.h"

t_object	*create_obj(int type, void (*onClick)(void *, int), int value, t_vector2 pos, t_vector2 size, int color, char *tag, t_object *victim)
{
	t_object	*result;
	
	result = malloc(sizeof(t_object));
	result->clickFunc = onClick;
	result->pos = pos;
	result->size = size;
	result->tag  = tag;
	result->type = type;
	result->value = value;
	result->color = color;
	result->victim = victim;
	return (result);
}

t_object_list	*get_last_object(t_object_list *start)
{
	if (!start)
		return (NULL);
	while (start->next)
		start = start->next;
	return (start);
}

t_object_list	*new_object_list(t_object *obj)
{
	t_object_list	*result;

	result = malloc(sizeof(t_object_list));
	result->next = NULL;
	result->object = obj;
	printf("new object of type %d\n", result->object->type);
	return (result);
}

void	add_obj_to_list(t_object_list **lst, t_object *obj)
{
	t_object_list	*last;

	last = get_last_object(*lst);
	if (!last)
	{
		*lst = new_object_list(obj);
		return ;
	}
	last->next = new_object_list(obj);
}

void	free_object_list(t_object_list *start)
{
	t_object_list	*tmp;

	if (!start)
		return ;
	while (start)
	{
		tmp = start->next;
		if (start->object)
			free(start->object);
		free(start);
		start = tmp;
	}
}

void	check_if_obj_clicked(t_vector2 mouse_pos, t_object_list *lst)
{
	while (lst)
	{
		if (check_vector_in_zone(mouse_pos, lst->object->pos, add_vec2(lst->object->pos, lst->object->size)) == TRUE && lst->object->clickFunc)
		{
			lst->object->clickFunc(lst->object->victim, lst->object->value + 1);
			return ;
		}
		lst = lst->next;
	}
}