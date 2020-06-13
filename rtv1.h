/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: openelop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 13:24:07 by openelop          #+#    #+#             */
/*   Updated: 2020/01/27 13:58:29 by lvania           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>



//# include <mlx.h>



# include <math.h>
# include <pthread.h>



# include </home/progerdaniil/Desktop/minilibx-master/mlx.h>


# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define THREADS_NUM 8
# define VIEWPORT_WIDTH 1
# define VIEWPORT_HEIGHT 1
# define VIEWPORT_DISTANCE 1
# define INF 999999999
# define NO_INTERSECTIONS -1
# define PI 3.1415926
# define RECUR_DEPTH 3

typedef struct	s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_figure
{
	char		*type;
	t_vector	center;
	t_vector	direction;
	double		radius;
	t_vector	colour;
	double		shine_idx;
	double		reflective;
}				t_figure;

typedef struct	s_light
{
	t_vector	cent_or_dir;
	char		*type;
	double		intensity;
}				t_light;

typedef struct	s_camera
{
	t_vector	center;
	t_vector	direction;
}				t_camera;

typedef struct	s_vec_par
{
	t_vector	o_big;
	t_vector	p_big;
	t_vector	l_big;
	t_vector	normal;
	double		n_dot_l;
	t_vector	r_big;
	t_vector	v_big;
	double		r_dot_v;
}				t_vec_par;

typedef struct	s_maxmin
{
	double		t_max;
	double		t_min;
}				t_maxmin;

typedef struct	s_inter_res
{
	double		closest_t;
	int			closest_figure;
	t_vector	start;
	t_vector	direction;
}				t_inter_res;

typedef struct	s_param
{
	int			start_light_num;
	int			start_fig_num;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*mlx_data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_figure	*figures;
	int			figures_num;
	t_camera	camera;
	t_light		*lights;
	int			lights_num;
	t_vector	curr_colour;
	int			image_counter;
	double		lighting_intensity;
	t_maxmin	t_max_min;
	int			recur_depth;
	t_vector	d_dir;
	t_vec_par	vec_params;
}				t_param;

typedef struct	s_for_threads
{
	t_param		param;
	int			thread_num;
}				t_for_threads;

typedef struct	s_square_equation
{
	int			fig_num;
	double		k1;
	double		k2;
	double		k3;
	double		discr;
	double		t1;
	double		t2;
}				t_square_equation;

typedef struct	s_plane_par
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		m;
	double		n;
	double		p;
	double		x1;
	double		y1;
	double		z1;
}				t_plane_par;

typedef struct	s_cylinder_par
{
	double		l;
	double		m;
	double		n;
	double		x1;
	double		y1;
	double		z1;
	double		r;
}				t_cylinder_par;

typedef struct	s_cone_par
{
	double		l;
	double		m;
	double		n;
	double		x1;
	double		y1;
	double		z1;
	double		s;
	double		h_big;
}				t_cone_par;

typedef struct	s_trace_ray_par
{
	t_vector	local_colour;
	t_vector	reflected_colour;
	t_vector	normal;
	t_vector	p_big;
	t_vector	r_big;
}				t_trace_ray_par;

/*
** main.c
*/

void			get_direction(t_param *param, int x, int y);
void			set_colour_to_image(t_param *param, int x, int y);
void			*scene_drawer(void *thr_param_void);
void			render(t_param *param);

/*
** parser.c
*/

t_vector		make_vector(char *line);
void			camera_parse(t_param *param, char **line);
void			light_parse(t_param *param, char **line);
void			figures_parse(t_param *param, char **line);
void			parser(char *name, t_param *param);

/*
** vector_operations.c
*/

t_vector		vec_substr(t_vector *vec1, t_vector *vec2);
double			dot_product(t_vector *vec1, t_vector *vec2);
double			get_vector_length(t_vector *vec);
t_vector		mult_vector_on_constant(t_vector vec, double constant);
t_vector		vec_sum(t_vector vec1, t_vector vec2);

/*
** intersecters.c
*/

void			intersect_decider(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq);
void			intersect_sphere(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq);
void			intersect_plane(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq);
void			intersect_cone(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq);
void			intersect_cylinder(t_param *param, t_vector start,
	t_vector direction, t_square_equation *sqr_eq);

/*
** trace_ray.c
*/

t_vector		reflect_ray(t_vector vec1, t_vector vec2);
t_vector		trace_ray(t_param *param, t_vector start,
	t_vector direction);
t_inter_res		look_for_intersections(t_param *param, t_vector start,
	t_vector direction);
void			set_closest_fig_and_t(t_param *param,
	t_square_equation *sqr_eq, int i, t_inter_res *inter_res);
t_vector		set_curr_colour(t_param *param, t_inter_res *inter_res);

/*
** lighting.c
*/

void			get_lighting_params(t_param *param, t_inter_res *inter_res);
void			compute_lighting(t_param *param, t_inter_res *inter_res);
void			compute_diffuseness(t_param *param, int i);
void			compute_shine(t_param *param, int i, t_inter_res *inter_res);
int				compute_shadow(t_param *param, int *i);

/*
** help_functions.c
*/

void			close_window(void *param_void);
int				key_press_down(int keycode, void *param_void);
t_vector		rotate_vector(t_vector vec, t_vector rotate, int s);
void			count_roots(t_square_equation *sqr_eq);
void			get_normal(t_param *param, t_inter_res *inter_res,
	t_vector start, t_vector direction);

/*
** validator.c
*/

int				camera_valid(char **splitted);
int				light_valid(char **splitted);
int				figure_valid(char **splitted);
int				validator(char *name, t_param *param);
int				check_type(char **splt, t_param *param);

/*
** validator_helpers.c
*/

int				vector_typed(char *str);
int				figure_typed(char **splt);
void			display_usage(void);
void			initializer(t_param *param);

#endif
