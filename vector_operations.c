#include "rtv1.h"

t_vector	vec_substr(t_vector *vec1, t_vector *vec2)
{
	t_vector res;

	res.x = vec1->x - vec2->x;
	res.y = vec1->y - vec2->y;
	res.z = vec1->z - vec2->z;
	return (res);
}

t_vector	vec_sum(t_vector vec1, t_vector vec2)
{
	t_vector res;

	res.x = vec1.x + vec2.x;
	res.y = vec1.y + vec2.y;
	res.z = vec1.z + vec2.z;
	return (res);
}

double		dot_product(t_vector *vec1, t_vector *vec2)
{
	double	res;

	res = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	return (res);
}

double		get_vector_length(t_vector *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

t_vector	mult_vector_on_constant(t_vector vec, double constant)
{
	t_vector	res;

	res.x = vec.x * constant;
	res.y = vec.y * constant;
	res.z = vec.z * constant;
	return (res);
}
