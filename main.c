#include "rtv1.h"

void		get_direction(t_param *param, int x, int y)
{
	//t_vector	xyz;

	param->d_dir.x = (double)(x - WINDOW_WIDTH / 2)
		* VIEWPORT_WIDTH / WINDOW_WIDTH;
	param->d_dir.y = (double)(WINDOW_HEIGHT / 2 - y)
		* VIEWPORT_HEIGHT / WINDOW_HEIGHT;
	param->d_dir.z = VIEWPORT_DISTANCE;
	//xyz = param->d_dir;
	param->d_dir = rotate_vector(param->d_dir, param->camera.direction, 1);
}

void		set_colour_to_image(t_param *param, int x, int y)
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

void		*scene_drawer(void *thr_param_void)
{
	int				x;
	int				y;
	t_for_threads	*thr_param;

	thr_param = (t_for_threads *)thr_param_void;
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = thr_param->thread_num * (WINDOW_HEIGHT / THREADS_NUM) - 1;
		while (++y < (thr_param->thread_num + 1)
			* (WINDOW_HEIGHT / THREADS_NUM))
		{
			get_direction(&(thr_param->param), x, y);
			thr_param->param.recur_depth = RECUR_DEPTH;
			thr_param->param.t_max_min.t_max = INF;
			thr_param->param.t_max_min.t_min = 1;
			thr_param->param.curr_colour = trace_ray(&(thr_param->param),
			thr_param->param.camera.center, thr_param->param.d_dir);
			set_colour_to_image(&(thr_param->param), x, y);
		}
	}
	return (NULL);
}

void		render(t_param *param)
{
	int				i;
	t_for_threads	wtf[THREADS_NUM];
	pthread_t		threads[THREADS_NUM];

	i = 0;
	while (i < THREADS_NUM)
	{
		wtf[i].param = *param;
		wtf[i].thread_num = i;
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_create(&(threads[i]), NULL, scene_drawer, &wtf[i]);
		i++;
	}
	i = 0;
	while (i < THREADS_NUM)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(param->mlx_ptr, param->win_ptr,
		param->img_ptr, 0, 0);
}

int			main(int argc, char **argv)
{
	t_param			param;

	initializer(&param);
	if (argc != 2 || validator(argv[1], &param) == 0)
	{
		display_usage();
		return (0);
	}
	param.figures = (t_figure*)malloc(sizeof(t_figure) * (param.start_fig_num));
	param.lights = (t_light*)malloc(sizeof(t_light) * param.start_light_num);
	param.mlx_ptr = mlx_init();
	param.win_ptr = mlx_new_window(param.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "Eto moe okno");
	param.img_ptr = mlx_new_image(param.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	param.mlx_data_addr = mlx_get_data_addr(param.img_ptr,
		&param.bpp, &param.size_line, &param.endian);
	parser(argv[1], &param);
	render(&param);
	mlx_hook(param.win_ptr, 2, 1L << 0, &key_press_down, (void*)&param);
	mlx_loop(param.mlx_ptr);
	return (0);
}
