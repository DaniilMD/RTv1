/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersecters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:59:02 by openelop          #+#    #+#             */
/*   Updated: 2020/01/02 16:59:05 by openelop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		intersect_decider(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	if (ft_strcmp(param->figures[sqr_eq->fig_num].type, "sphere:") == 0)
		intersect_sphere(param, start, direction, sqr_eq);
	else if (ft_strcmp(param->figures[sqr_eq->fig_num].type, "plane:") == 0)
		intersect_plane(param, start, direction, sqr_eq);
	else if (ft_strcmp(param->figures[sqr_eq->fig_num].type, "cone:") == 0)
		intersect_cone(param, start, direction, sqr_eq);
	else if (ft_strcmp(param->figures[sqr_eq->fig_num].type, "cylinder:") == 0)
		intersect_cylinder(param, start, direction, sqr_eq);
}

void		intersect_sphere(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	t_vector	oc;
	double		radius;

	radius = param->figures[sqr_eq->fig_num].radius;
	oc = vec_substr(&start, &(param->figures[sqr_eq->fig_num].center));
	sqr_eq->k1 = dot_product(&(direction), &(direction));
	sqr_eq->k2 = 2 * dot_product(&oc, &(direction));
	sqr_eq->k3 = dot_product(&oc, &oc) - radius * radius;
	sqr_eq->discr = sqr_eq->k2 * sqr_eq->k2 - 4 * sqr_eq->k1 * sqr_eq->k3;
	if (sqr_eq->discr < 0)
	{
		sqr_eq->t1 = INF;
		sqr_eq->t2 = INF;
		return ;
	}
	sqr_eq->t1 = (0 - sqr_eq->k2 + sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
	sqr_eq->t2 = (0 - sqr_eq->k2 - sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
}

void		intersect_plane(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	/*double	c;
	double	t;

	c = dot_product(&(direction), &(param->figures[sqr_eq->fig_num].direction));
	if (c == 0)
	{
		sqr_eq->t1 = INF;
		sqr_eq->t2 = INF;
		return ;
	}
	t = (param->figures[sqr_eq->fig_num].radius - dot_product(&(start),
	&(param->figures[sqr_eq->fig_num].direction))) / c;
	if (t < 0)
	{
		sqr_eq->t1 = INF;
		sqr_eq->t2 = INF;
		return ;
	}
	sqr_eq->t1 = t;
	sqr_eq->t2 = t;
	return ;*/
	double A;
	double B;
	double C;
	double D;
	double m;
	double n;
	double p;
	double x1;
	double y1;
	double z1;
	A = param->figures[sqr_eq->fig_num].direction.x;
	B = param->figures[sqr_eq->fig_num].direction.y;
	C = param->figures[sqr_eq->fig_num].direction.z;
	D = param->figures[sqr_eq->fig_num].radius;
	x1 = start.x;
	y1 = start.y;
	z1 = start.z;
	m = direction.x;
	n = direction.y;
	p = direction.z;
	if (A * m + B * n + C * p == 0)
	{
		sqr_eq->t1 = INF;
		sqr_eq->t2 = INF;
		return ;
	}
	else
	{
		sqr_eq->t1 = -(A * x1 + B * y1 + C * z1 + D) / (A * m + B * n + C * p);
	}
}

void		intersect_cone(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{



}



void		intersect_cylinder(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	double A;
	double B;
	double l;
	double m;
	double n;
	double x1;
	double y1;
	double z1;
	t_vector help;
	help.x = 90 * PI / 180;
	help.y = 0;
	help.z = 0;
	start = rotate_vector(start, param->figures[sqr_eq->fig_num].direction);
	direction = rotate_vector(direction, param->figures[sqr_eq->fig_num].direction);
	start = rotate_vector(start, help);
	direction = rotate_vector(direction, help);
	A = param->figures[sqr_eq->fig_num].radius;//center.x;
	B = param->figures[sqr_eq->fig_num].radius;//center.y;
	x1 = start.x;
	y1 = start.y;
	z1 = start.z;
	l = direction.x;
	m = direction.y;
	n = direction.z;
	sqr_eq->k1 = (B * B * l * l + A * A * m * m);
	sqr_eq->k2 = 2 * (B * B * l * x1 + A * A * m * y1);
	sqr_eq->k3 = (B * B * x1 * x1 + A * A * y1 * y1 - A * A * B * B);
	sqr_eq->discr = sqr_eq->k2 * sqr_eq->k2 - 4 * sqr_eq->k1 * sqr_eq->k3;
	if (sqr_eq->discr > 0)
	{
		//printf("sss)))\n");
		sqr_eq->t1 = (0 - sqr_eq->k2 + sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
		sqr_eq->t2 = (0 - sqr_eq->k2 - sqrt(sqr_eq->discr)) / (2 * sqr_eq->k1);
		//printf("%f %f\n", sqr_eq->t1, sqr_eq->t2);
		return ;
	}
	//printf("wefweergergreg)))\n");
	sqr_eq->t1 = INF;
	sqr_eq->t2 = INF;
}
