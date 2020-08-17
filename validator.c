#include "rtv1.h"

int			camera_valid(char **splt)
{
	if (splt[1] == 0 || vector_typed(splt[1]) == 0)
		return (0);
	if (splt[2] == 0 || vector_typed(splt[2]) == 0)
		return (0);
	if (splt[3] != 0)
		return (0);
	return (1);
}

int			light_valid(char **splt)
{
	if (ft_strcmp(splt[1], "point") != 0
			&& ft_strcmp(splt[1], "ambient") != 0
			&& ft_strcmp(splt[1], "directional") != 0)
		return (0);
	if (ft_strcmp(splt[1], "ambient") == 0)
	{
		if (splt[2] == 0)
			return (0);
		if (splt[3] != 0)
			return (0);
	}
	else
	{
		if (splt[2] == 0 || vector_typed(splt[2]) == 0)
			return (0);
		if (splt[3] == 0)
			return (0);
		if (splt[4] != 0)
			return (0);
	}
	return (1);
}

int			figure_valid(char **splt)
{
	if (splt[1] == 0 || vector_typed(splt[1]) == 0)
		return (0);
	if (splt[2] == 0 || vector_typed(splt[2]) == 0)
		return (0);
	if (splt[3] == 0)
		return (0);
	if (splt[4] == 0 || vector_typed(splt[4]) == 0)
		return (0);
	if (splt[5] == 0)
		return (0);
	if (splt[6] == 0)
		return (0);
	if (splt[7] != 0)
		return (0);
	return (1);
}

int			check_type(char **splt, t_param *param)
{
	if (figure_typed(splt) == 0 && ft_strcmp(splt[0], "camera:") != 0
			&& ft_strcmp(splt[0], "light:") != 0)
		return (0);
	if (ft_strcmp(splt[0], "camera:") == 0)
		if (camera_valid(splt) == 0)
			return (0);
	if (ft_strcmp(splt[0], "light:") == 0)
	{
		param->start_light_num++;
		if (light_valid(splt) == 0)
			return (0);
	}
	if (figure_typed(splt) == 1)
	{
		param->start_fig_num++;
		if (figure_valid(splt) == 0)
			return (0);
	}
	return (1);
}

int			validator(char *name, t_param *param)
{
	int		fd;
	char	*line;
	char	**splt;
	int		ret;

	if ((fd = open(name, O_RDWR)) < 0)
		return (0);
	param->start_fig_num = 0;
	param->start_light_num = 0;
	while ((ret = get_next_line(fd, &line)) != 0)
	{
		if (ft_strlen(line) < 1)
			return (0);
		splt = ft_strsplit(line, ' ');
		if (!check_type(splt, param))
			return (0);
		free_char_starstar(splt);
		free(line);
	}
	return (1);
}
