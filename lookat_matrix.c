/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookat_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 16:22:44 by ncharret          #+#    #+#             */
/*   Updated: 2015/07/03 15:12:38 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void create_lookat_matrix(t_matrix mtx, t_vector e, t_vector trgt, t_vector up)
{
	t_vector	f;
	t_vector	u;
	t_vector	s;

	f = norm_vector(sub_vector(trgt, e));
	u = norm_vector(up);
	s = norm_vector(cross_product(f, u));
	u = cross_product(s, f);
	mtx[0][0] = s.x;
	mtx[0][1] = u.x;
	mtx[0][2] = -f.x;
	mtx[0][3] = 0;
	mtx[1][0] = s.y;
	mtx[1][1] = u.y;
	mtx[1][2] = -f.y;
	mtx[1][3] = 0;
	mtx[2][0] = s.z;
	mtx[2][1] = u.z;
	mtx[2][2] = -f.z;
	mtx[2][3] = 0;
	mtx[3][0] = -dot_product(s, e);
	mtx[3][1] = -dot_product(u, e);
	mtx[3][2] = dot_product(f, e);
	mtx[3][3] = 1;
}
