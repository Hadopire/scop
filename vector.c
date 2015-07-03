/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 19:52:03 by ncharret          #+#    #+#             */
/*   Updated: 2015/05/14 18:18:35 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vector	init_vector(float x, float y, float z)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = 1.0;
	return (vector);
}

t_vector	sub_vector(t_vector a, t_vector b)
{
	t_vector vector;

	vector.x = a.x - b.x;
	vector.y = a.y - b.y;
	vector.z = a.z - b.z;
	return (vector);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector vector;

	vector.x = (a.y * b.z) - (a.z * b.y);
	vector.y = (a.z * b.x) - (a.x * b.z);
	vector.z = (a.x * b.y) - (a.y * b.x);
	return (vector);
}

float		magnitude(t_vector a)
{
	float result;

	result = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);
	result = result ? sqrt(result) : 0;
	return (result);
}

t_vector	norm_vector(t_vector a)
{
	t_vector	vector;
	float		magn;

	magn = magnitude(a);
	vector.x = magn == 0 ? 0 : a.x / magn;
	vector.y = magn == 0 ? 0 : a.y / magn;
	vector.z = magn == 0 ? 0 : a.z / magn;
	return (vector);
}
