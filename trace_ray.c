/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:58:53 by openelop          #+#    #+#             */
/*   Updated: 2020/01/02 16:58:55 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		reflect_ray(t_vector vec1, t_vector vec2)
{
	t_vector	res;

	res = mult_vector_on_constant(vec2, 2 * dot_product(&vec2, &vec1));
	res = vec_substr(&res, &vec1);
    return (res);
}

t_vector		trace_ray(t_param *param, t_vector start,
	t_vector direction)
{
	t_inter_res			inter_res;


	t_vector			local_colour;
	t_vector			reflected_colour;
	t_vector			normal;
	t_vector			p_big;
	t_vector			r_big;


	inter_res = look_for_intersections(param, start, direction);
	param->lighting_intensity = 0;
	if (inter_res.closest_figure != NO_INTERSECTIONS)
		compute_lighting(param, &inter_res);
	local_colour = set_curr_colour(param, &inter_res);
	////////////////////////////////////////////////////////////
	//return (local_colour);

	//local_colour = param->curr_colour;
	if ((param->recur_depth <= 0) || (param->figures[inter_res.closest_figure].reflective <= 0))
		return (local_colour);


	p_big =  vec_sum(start,
		mult_vector_on_constant(direction, inter_res.closest_t));

	normal = vec_substr(&p_big, &(param->figures[inter_res.closest_figure].center));
	normal = mult_vector_on_constant(normal, 1 / get_vector_length(&normal));

	param->t_max_min.t_max = INF;
	param->t_max_min.t_min = 0.001;
	param->recur_depth--;

	r_big = reflect_ray(mult_vector_on_constant(direction, -1), normal);

	reflected_colour = trace_ray(param, p_big, r_big);

	//param->t_max_min.t_max = INF;
	//		param->t_max_min.t_min = 1;


	return (vec_sum(mult_vector_on_constant(local_colour,
	(1 - param->figures[inter_res.closest_figure].reflective)),
	mult_vector_on_constant(reflected_colour,
	param->figures[inter_res.closest_figure].reflective)));
	/////////////////////////////////////////////////////////////////////////
}

t_inter_res		look_for_intersections(t_param *param, t_vector start,
	t_vector direction)
{
	int					i;
	t_inter_res			inter_res;
	t_square_equation	sqr_eq;

	inter_res.closest_figure = NO_INTERSECTIONS;
	inter_res.closest_t = INF;
	i = 0;
	while (i < param->figures_num)
	{
		sqr_eq.fig_num = i;
		intersect_decider(param, start, direction, &sqr_eq);
		set_closest_fig_and_t(param, &sqr_eq, i, &inter_res);
		i++;
	}
	inter_res.direction = direction;
	inter_res.start = start;
	return (inter_res);
}

void		set_closest_fig_and_t(t_param *param,
	t_square_equation *sqr_eq, int i, t_inter_res *inter_res)
{
	if ((sqr_eq->t1 > param->t_max_min.t_min) && (sqr_eq->t1 <
	param->t_max_min.t_max) && (sqr_eq->t1 < inter_res->closest_t))
	{
		inter_res->closest_t = sqr_eq->t1;
		inter_res->closest_figure = i;
	}
	if ((sqr_eq->t2 > param->t_max_min.t_min) && (sqr_eq->t2 <
	param->t_max_min.t_max) && (sqr_eq->t2 < inter_res->closest_t))
	{
		inter_res->closest_t = sqr_eq->t2;
		inter_res->closest_figure = i;
	}
}

t_vector		set_curr_colour(t_param *param, t_inter_res *inter_res)
{
	t_vector	colour;

	colour.x = param->figures[inter_res->closest_figure].colour.x
		* param->lighting_intensity;
	colour.y = param->figures[inter_res->closest_figure].colour.y
		* param->lighting_intensity;
	colour.z = param->figures[inter_res->closest_figure].colour.z
		* param->lighting_intensity;
	if (colour.x > 255)
		colour.x = 255;
	if (colour.y > 255)
		colour.y = 255;
	if (colour.z > 255)
		colour.z = 255;
	return (colour);
}