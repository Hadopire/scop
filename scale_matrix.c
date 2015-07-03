/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 16:22:04 by ncharret          #+#    #+#             */
/*   Updated: 2015/07/03 14:29:27 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void create_scale_matrix(t_matrix mtx, float factor)
{
	mtx[0][0] = factor;
	mtx[0][1] = 0;
	mtx[0][2] = 0;
	mtx[0][3] = 0;
	mtx[1][0] = 0;
	mtx[1][1] = factor;
	mtx[1][2] = 0;
	mtx[1][3] = 0;
	mtx[2][0] = 0;
	mtx[2][1] = 0;
	mtx[2][2] = factor;
	mtx[2][3] = 0;
	mtx[3][0] = 0;
	mtx[3][1] = 0;
	mtx[3][2] = 0;
	mtx[3][3] = 1;
}
