/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:29:47 by openelop          #+#    #+#             */
/*   Updated: 2020/01/06 14:30:02 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		close_window(void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	free(param->figures);
	free(param->lights);
	(void)param;
	exit(0);
}

int			key_press_down(int keycode, void *param_void)
{
	t_param			*param;

	param = (t_param *)param_void;
	if (keycode == 0xff1b)
		close_window(param_void);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	render(param_void);
	return (0);
}

t_vector	rotate_vector(t_vector vec, t_vector rotate, int s)
{
	t_vector vec_res;

	vec_res = vec;
	if (rotate.x != 0)
	{
		vec.y = vec_res.y * cos(s * rotate.x) + vec_res.z * sin(s * rotate.x);
		vec.z = -vec_res.y * sin(s * rotate.x) + vec_res.z * cos(s * rotate.x);
	}
	vec_res = vec;
	if (rotate.y != 0)
	{
		vec.x = vec_res.x * cos(s * rotate.y) + vec_res.z * sin(s * rotate.y);
		vec.z = -vec_res.x * sin(s * rotate.y) + vec_res.z * cos(s * rotate.y);
	}
	vec_res = vec;
	if (rotate.z != 0)
	{
		vec.x = vec_res.x * cos(s * rotate.z) - vec_res.y * sin(s * rotate.z);
		vec.y = vec_res.x * sin(s * rotate.z) + vec_res.y * cos(s * rotate.z);
	}
	return (vec);
}

void		count_roots(t_square_equation *sqr_eq)
{
	if (sqr_eq->discr > 0)
	{
		sqr_eq->t1 = (0 - sqr_eq->k2 + sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
		sqr_eq->t2 = (0 - sqr_eq->k2 - sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
		return ;
	}
	sqr_eq->t1 = INF;
	sqr_eq->t2 = INF;
}

void		get_normal(t_param *param, t_inter_res *inter_res,
	t_vector start, t_vector direction)
{
	t_vector	cent;
	t_vector	p_big_alt;

	start = inter_res->start;
	direction = inter_res->direction;
	start = vec_substr(&start,
		&(param->figures[inter_res->closest_figure].center));
	start = rotate_vector(start,
		param->figures[inter_res->closest_figure].direction, -1);
	direction = rotate_vector(direction,
		param->figures[inter_res->closest_figure].direction, -1);
	p_big_alt = vec_sum(start,
		mult_vector_on_constant(direction, inter_res->closest_t));
	cent.x = 0;
	if (ft_strcmp(param->figures[inter_res->closest_figure].type,
	"cone:") == 0)
		cent.y = get_vector_length(&p_big_alt) / cos(param->figures[inter_res->
		closest_figure].radius * PI / 180) * ((p_big_alt.y < 0) ? -1 : 1);
	else if (ft_strcmp(param->figures[inter_res->closest_figure].type,
	"cylinder:") == 0)
		cent.y = p_big_alt.y;
	cent.z = 0;
	param->vec_params.normal = vec_substr(&(p_big_alt), &cent);
	param->vec_params.normal = rotate_vector(param->vec_params.normal,
		param->figures[inter_res->closest_figure].direction, 1);
}
