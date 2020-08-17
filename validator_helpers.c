#include "rtv1.h"

int			vector_typed(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
		{
			if (str[i + 1] == ',')
				return (0);
			counter++;
		}
		i++;
	}
	if (counter != 2)
		return (0);
	return (1);
}

int			figure_typed(char **splt)
{
	if (ft_strcmp(splt[0], "sphere:") != 0
	&& ft_strcmp(splt[0], "plane:") != 0
	&& ft_strcmp(splt[0], "cylinder:") != 0
	&& ft_strcmp(splt[0], "cone:") != 0)
		return (0);
	return (1);
}

void		initializer(t_param *param)
{
	param->start_fig_num = 0;
	param->start_light_num = 0;
	param->figures_num = 0;
	param->lights_num = 0;
	param->image_counter = 0;
	param->lighting_intensity = 0;
}

void		display_usage(void)
{
	ft_putstr("Error\nInstruction:\n\t1) No empty lines\n\
\t2) No invalid files\n\t3) Follow these patterns:\n\
\t1) camera: [position_vector] [look_direction_vector]\n\
\t2.1) light: point [position_vector] [intensity]\n\
\t2.2) light: directional [direction_vector] [intensity]\n\
\t2.3) light: ambient [intensity]\n\
\t3) figure: [sphere/plane/cylinder/cone] [position_vector] [rotate_vector]\\\n\
\t\t[parameter] [colour_vector] [shine_index] [reflection_index]\\n\n\
Comments: \n\t\"vector\" means this format: [int_num],[int_num],[int_num]\n\
\t\"parameter\" for figures means: \n\t\t1) radius for sphere\n\t\t\
2) D param for plane\n\t\t3) circle radius for cylinder\n\t\t\
4) foundation angle for cone\n\
\t[rotate_vector] for plane means nothing\n\
\t[position vector] for plane means A, B, C plane normal params\n\
\t[rotate vector] and [parameter] for cone entered in degrees\n");
}
