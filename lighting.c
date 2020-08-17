#include "rtv1.h"

void		get_lighting_params(t_param *param, t_inter_res *inter_res)
{
	t_vector	start;
	t_vector	direction;

	start = param->vec_params.l_big;
	direction = param->vec_params.l_big;
	param->vec_params.p_big = vec_sum(inter_res->start,
	mult_vector_on_constant(inter_res->direction, inter_res->closest_t));
	if (ft_strcmp(param->figures[inter_res->closest_figure].type,
		"sphere:") == 0)
		param->vec_params.normal = vec_substr(&(param->vec_params.p_big),
		&(param->figures[inter_res->closest_figure].center));
	else if (ft_strcmp(param->figures[inter_res->closest_figure].type,
		"plane:") == 0)
		param->vec_params.normal =
			param->figures[inter_res->closest_figure].center;
	else if (ft_strcmp(param->figures[inter_res->closest_figure].type,
		"cone:") == 0)
		get_normal(param, inter_res, start, direction);
	else if (ft_strcmp(param->figures[inter_res->closest_figure].type,
		"cylinder:") == 0)
		get_normal(param, inter_res, start, direction);
	param->vec_params.normal = mult_vector_on_constant(param->vec_params.normal,
	1 / get_vector_length(&(param->vec_params.normal)));
}

void		compute_lighting(t_param *param, t_inter_res *inter_res)
{
	int	i;

	i = 0;
	param->lighting_intensity = 0;
	get_lighting_params(param, inter_res);
	while (i < param->lights_num)
	{
		if (ft_strcmp(param->lights[i].type, "ambient") == 0)
			param->lighting_intensity += param->lights[i].intensity;
		else
		{
			if (ft_strcmp(param->lights[i].type, "point") == 0)
				param->vec_params.l_big = vec_substr(
	&(param->lights[i].cent_or_dir), &(param->vec_params.p_big));
			else
				param->vec_params.l_big = param->lights[i].cent_or_dir;
			if (compute_shadow(param, &i) == 1)
				continue ;
			compute_diffuseness(param, i);
			if (param->figures[inter_res->closest_figure].shine_idx != -1)
				compute_shine(param, i, inter_res);
		}
		i++;
	}
}

void		compute_diffuseness(t_param *param, int i)
{
	param->vec_params.n_dot_l = dot_product(&(param->vec_params.normal),
	&(param->vec_params.l_big));
	if (param->vec_params.n_dot_l > 0)
		param->lighting_intensity += param->lights[i].intensity *
	param->vec_params.n_dot_l / (get_vector_length(&(param->vec_params.normal))
		* get_vector_length(&(param->vec_params.l_big)));
}

void		compute_shine(t_param *param, int i, t_inter_res *inter_res)
{
	param->vec_params.v_big.x = -param->d_dir.x;
	param->vec_params.v_big.y = -param->d_dir.y;
	param->vec_params.v_big.z = -param->d_dir.z;
	param->vec_params.r_big = reflect_ray(param->vec_params.l_big,
		param->vec_params.normal);
	param->vec_params.r_dot_v = dot_product(&(param->vec_params.r_big),
		&(param->vec_params.v_big));
	if (param->vec_params.r_dot_v > 0)
		param->lighting_intensity += param->lights[i].intensity *
	pow(param->vec_params.r_dot_v / (get_vector_length(&(param->
	vec_params.r_big)) * get_vector_length(&(param->vec_params.v_big))),
	param->figures[inter_res->closest_figure].shine_idx);
}

int			compute_shadow(t_param *param, int *i)
{
	t_inter_res		inter_res_shadow;

	param->t_max_min.t_min = 0.001;
	if (ft_strcmp(param->lights[*i].type, "point") == 0)
		param->t_max_min.t_max = 1;
	else if (ft_strcmp(param->lights[*i].type, "direction") == 0)
		param->t_max_min.t_max = INF;
	inter_res_shadow = look_for_intersections(param, param->vec_params.p_big,
	param->vec_params.l_big);
	if (inter_res_shadow.closest_t == INF)
		return (0);
	*i += 1;
	return (1);
}
