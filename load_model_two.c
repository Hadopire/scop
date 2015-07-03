/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_model_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/03 15:10:55 by ncharret          #+#    #+#             */
/*   Updated: 2015/07/03 15:12:22 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		generate_uv(t_mesh *mesh)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	mesh->uv = (GLfloat*)malloc(sizeof(GLfloat) *
			(mesh->vertex_count * (2.f / 3.f) + 1));
	while (i < mesh->vertex_count)
	{
		mesh->uv[a] = mesh->vtx[i] + mesh->vtx[i + 2];
		mesh->uv[a + 1] = mesh->vtx[i] + mesh->vtx[i + 1];
		i += 3;
		a += 2;
	}
}

float		compute_average(GLfloat *vtx, int size, int i)
{
	int		a;
	float	min;
	float	max;

	min = vtx[i];
	max = vtx[i];
	a = 3;
	while (a < size)
	{
		if (min > vtx[a + i])
			min = vtx[a + i];
		if (max < vtx[a + i])
			max = vtx[a + i];
		a += 3;
	}
	return ((max + min) / 2.f);
}

void		center_mesh(t_mesh *mesh)
{
	t_matrix	mtx;
	float		averagex;
	float		averagey;
	float		averagez;

	averagex = compute_average(mesh->vtx, mesh->vertex_count / 3, 0);
	averagey = compute_average(mesh->vtx, mesh->vertex_count / 3, 1);
	averagez = compute_average(mesh->vtx, mesh->vertex_count / 3, 2);
	create_translation_matrix(init_vector(-averagex, -averagey, -averagez),
			mtx);
	transform_model(mesh->vtx, mtx, mesh->vertex_count);
}

void		fill_normals(t_mesh *mesh)
{
	int			i;
	t_vector	v1;
	t_vector	v2;
	t_vector	v3;

	mesh->normals = malloc(sizeof(GLfloat) * mesh->vertex_count);
	i = 0;
	while (i < mesh->vertex_count)
	{
		v1 = init_vector(mesh->vtx[i], mesh->vtx[i + 1], mesh->vtx[i + 2]);
		v2 = init_vector(mesh->vtx[i + 3], mesh->vtx[i + 4], mesh->vtx[i + 5]);
		v3 = init_vector(mesh->vtx[i + 6], mesh->vtx[i + 7], mesh->vtx[i + 8]);
		v1 = norm_vector(cross_product(sub_vector(v1, v2), sub_vector(v1, v3)));
		mesh->normals[i] = v1.x;
		mesh->normals[i + 1] = v1.y;
		mesh->normals[i + 2] = v1.z;
		mesh->normals[i + 3] = v1.x;
		mesh->normals[i + 4] = v1.y;
		mesh->normals[i + 5] = v1.z;
		mesh->normals[i + 6] = v1.x;
		mesh->normals[i + 7] = v1.y;
		mesh->normals[i + 8] = v1.z;
		i += 9;
	}
}
