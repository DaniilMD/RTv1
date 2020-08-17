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
	t_trace_ray_par		trp;

	param->lighting_intensity = 0;
	inter_res = look_for_intersections(param, start, direction);
	if (inter_res.closest_figure != NO_INTERSECTIONS)
		compute_lighting(param, &inter_res);
	trp.local_colour = set_curr_colour(param, &inter_res);
	if ((param->recur_depth-- <= 0) ||
		(param->figures[inter_res.closest_figure].reflective <= 0))
		return (trp.local_colour);
	trp.p_big = vec_sum(start,
		mult_vector_on_constant(direction, inter_res.closest_t));
	trp.normal = vec_substr(&(trp.p_big),
		&(param->figures[inter_res.closest_figure].center));
	trp.normal = mult_vector_on_constant(trp.normal,
		1 / get_vector_length(&(trp.normal)));
	param->t_max_min.t_max = INF;
	param->t_max_min.t_min = 0.001;
	trp.r_big = reflect_ray(mult_vector_on_constant(direction, -1), trp.normal);
	trp.reflected_colour = trace_ray(param, trp.p_big, trp.r_big);
	return (vec_sum(mult_vector_on_constant(trp.local_colour,
	(1 - param->figures[inter_res.closest_figure].reflective)),
	mult_vector_on_constant(trp.reflected_colour,
	param->figures[inter_res.closest_figure].reflective)));
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

void			set_closest_fig_and_t(t_param *param,
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


	// if (colour.x > 255 || colour.y > 255 || colour.x > 255)
	// {
	// 	colour.z = 255;
	// 	colour.y = 255;
	// 	colour.x = 255;
	// }



	// if (param->lighting_intensity > 1)
	// {
	// 	colour.z = 255;
	// 	colour.y = 255;
	// 	colour.x = 255;
	// }



	return (colour);
}
