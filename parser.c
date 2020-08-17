#include "rtv1.h"

t_vector	make_vector(char *line)
{
	t_vector	vec;
	char		**vector_split;

	vector_split = ft_strsplit(line, ',');
	vec.x = ft_atoi(vector_split[0]);
	vec.y = ft_atoi(vector_split[1]);
	vec.z = ft_atoi(vector_split[2]);
	free_char_starstar(vector_split);
	return (vec);
}

void		camera_parse(t_param *param, char **line)
{
	param->camera.center = make_vector(line[1]);
	param->camera.direction = make_vector(line[2]);
	param->camera.direction.x = param->camera.direction.x * PI / 180;
	param->camera.direction.y = param->camera.direction.y * PI / 180;
	param->camera.direction.z = param->camera.direction.z * PI / 180;
}

void		light_parse(t_param *param, char **line)
{
	int		i;

	i = param->lights_num;
	param->lights[i].type = ft_strdup(line[1]);
	if (ft_strcmp(param->lights[i].type, "ambient") == 0)
	{
		param->lights[i].intensity = (double)ft_atoi(line[2]) / 100;
		param->lights_num++;
		return ;
	}
	param->lights[i].cent_or_dir = make_vector(line[2]);
	param->lights[i].intensity = (double)ft_atoi(line[3]) / 100;
	param->lights_num++;
}

void		figures_parse(t_param *param, char **line)
{
	int		i;

	i = param->figures_num;
	param->figures[i].type = ft_strdup(line[0]);
	param->figures[i].center = make_vector(line[1]);
	param->figures[i].direction = make_vector(line[2]);
	param->figures[i].direction.x = param->figures[i].direction.x * PI / 180;
	param->figures[i].direction.y = param->figures[i].direction.y * PI / 180;
	param->figures[i].direction.z = param->figures[i].direction.z * PI / 180;
	param->figures[i].radius = ft_atoi(line[3]);
	param->figures[i].colour = make_vector(line[4]);
	param->figures[i].shine_idx = ft_atoi(line[5]);
	param->figures[i].reflective = (double)ft_atoi(line[6]) / 100;
	param->figures_num++;
}

void		parser(char *name, t_param *param)
{
	int		fd;
	char	*line;
	char	**splitted;
	int		i;
	int		ret;

	fd = open(name, O_RDONLY);
	i = 0;
	while ((ret = get_next_line(fd, &line)) != 0)
	{
		splitted = ft_strsplit(line, ' ');
		if (ft_strcmp(splitted[0], "camera:") == 0)
			camera_parse(param, splitted);
		else if (ft_strcmp(splitted[0], "light:") == 0)
			light_parse(param, splitted);
		else
			figures_parse(param, splitted);
		i++;
		free_char_starstar(splitted);
		free(line);
		if (ret == 0)
			return ;
	}
}
