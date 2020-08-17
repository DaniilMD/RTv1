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
	t_plane_par pl_par;

	pl_par.a = param->figures[sqr_eq->fig_num].center.x;
	pl_par.b = param->figures[sqr_eq->fig_num].center.y;
	pl_par.c = param->figures[sqr_eq->fig_num].center.z;
	pl_par.d = param->figures[sqr_eq->fig_num].radius;
	pl_par.x1 = start.x;
	pl_par.y1 = start.y;
	pl_par.z1 = start.z;
	pl_par.m = direction.x;
	pl_par.n = direction.y;
	pl_par.p = direction.z;
	if (pl_par.a * pl_par.m + pl_par.b * pl_par.n + pl_par.c * pl_par.p == 0)
	{
		sqr_eq->t1 = INF;
		sqr_eq->t2 = INF;
		return ;
	}
	else
	{
		sqr_eq->t1 = -(pl_par.a * pl_par.x1 + pl_par.b * pl_par.y1
		+ pl_par.c * pl_par.z1 + pl_par.d) / (pl_par.a * pl_par.m
		+ pl_par.b * pl_par.n + pl_par.c * pl_par.p);
		sqr_eq->t2 = sqr_eq->t1;
	}
}

void		intersect_cylinder(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	t_cylinder_par cyl_par;

	start = vec_substr(&start, &(param->figures[sqr_eq->fig_num].center));
	start = rotate_vector(start, param->figures[sqr_eq->fig_num].direction, -1);
	direction = rotate_vector(direction,
		param->figures[sqr_eq->fig_num].direction, -1);
	cyl_par.r = param->figures[sqr_eq->fig_num].radius;
	cyl_par.x1 = start.x;
	cyl_par.y1 = start.y;
	cyl_par.z1 = start.z;
	cyl_par.l = direction.x;
	cyl_par.m = direction.y;
	cyl_par.n = direction.z;
	sqr_eq->k1 = (cyl_par.l * cyl_par.l + cyl_par.n * cyl_par.n);
	sqr_eq->k2 = 2 * (cyl_par.l * cyl_par.x1 + cyl_par.n * cyl_par.z1);
	sqr_eq->k3 = (cyl_par.x1 * cyl_par.x1 +
		cyl_par.z1 * cyl_par.z1 - cyl_par.r * cyl_par.r);
	sqr_eq->discr = sqr_eq->k2 * sqr_eq->k2 - 4 * sqr_eq->k1 * sqr_eq->k3;
	count_roots(sqr_eq);
}

void		intersect_cone(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq)
{
	t_cone_par cone_par;

	start = vec_substr(&start, &(param->figures[sqr_eq->fig_num].center));
	start = rotate_vector(start, param->figures[sqr_eq->fig_num].direction, -1);
	direction = rotate_vector(direction,
		param->figures[sqr_eq->fig_num].direction, -1);
	cone_par.h_big = INF;
	cone_par.s = tan(param->figures[sqr_eq->fig_num].radius * PI / 180)
		* cone_par.h_big;
	cone_par.x1 = start.x;
	cone_par.y1 = start.y;
	cone_par.z1 = start.z;
	cone_par.l = direction.x;
	cone_par.m = direction.y;
	cone_par.n = direction.z;
	sqr_eq->k1 = (cone_par.n * cone_par.n * cone_par.h_big + cone_par.l
	* cone_par.l * cone_par.h_big - cone_par.m * cone_par.m * cone_par.s);
	sqr_eq->k2 = 2 * (cone_par.x1 * cone_par.l * cone_par.h_big + cone_par.z1
	* cone_par.n * cone_par.h_big - cone_par.y1 * cone_par.m * cone_par.s);
	sqr_eq->k3 = (cone_par.x1 * cone_par.x1 * cone_par.h_big + cone_par.z1
	* cone_par.z1 * cone_par.h_big - cone_par.y1 * cone_par.y1 * cone_par.s);
	sqr_eq->discr = sqr_eq->k2 * sqr_eq->k2 - 4 * sqr_eq->k1 * sqr_eq->k3;
	count_roots(sqr_eq);
}
