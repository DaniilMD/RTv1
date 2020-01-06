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

void	set_colour_to_image(t_param *param, int x, int y)
{
	param->image_counter = x * (param->bpp) / 8
	+ y * (param->size_line);
	param->mlx_data_addr[param->image_counter] =
		param->curr_colour.z;
	param->mlx_data_addr[param->image_counter + 1] =
		param->curr_colour.y;
	param->mlx_data_addr[param->image_counter + 2] =
		param->curr_colour.x;
}

void	close_window(void *param_void)
{
	t_param *param;

	param = (t_param*)param_void;
	mlx_destroy_image(param->mlx_ptr, param->img_ptr);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	(void)param;
	exit(0);
}

int		key_press_down(int keycode, void *param_void)
{
	t_param			*param;

	param = (t_param *)param_void;
	if (keycode == 53)
		close_window(param_void);
	mlx_clear_window(param->mlx_ptr, param->win_ptr);
	render(param_void);
	return (0);
}

t_vector	rotate_vector(t_vector vec, t_vector rotate)
{
	t_vector vec_res;

	vec_res = vec;
	if (rotate.x != 0)
	{
		vec.y = vec_res.y * cos(rotate.x) + vec_res.z * sin(rotate.x);
		vec.z = -vec_res.y * sin(rotate.x) + vec_res.z * cos(rotate.x);
	}
	vec_res = vec;
	if (rotate.y != 0)
	{
		vec.x = vec_res.x * cos(rotate.y) + vec_res.z * sin(rotate.y);
		vec.z = -vec_res.x * sin(rotate.y) + vec_res.z * cos(rotate.y);
	}
	vec_res = vec;
	if (rotate.z != 0)
	{
		vec.x = vec_res.x * cos(rotate.z) - vec_res.y * sin(rotate.z);
		vec.y = vec_res.x * sin(rotate.z) + vec_res.y * cos(rotate.z);
	}
	return (vec);
}
