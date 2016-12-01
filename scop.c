/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 16:27:38 by ncharret          #+#    #+#             */
/*   Updated: 2016/10/10 15:24:25 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

double		toradian(double angle)
{
	return (((M_PI * angle) / 180));
}

void		init_opengl(void)
{
	GLuint vertexarrayid;

	glGenVertexArrays(1, &vertexarrayid);
	glBindVertexArray(vertexarrayid);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void		update_win(t_env *a, int width, int height)
{
	a->width = width;
	a->height = height;
	a->ratio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

void		update_screen(GLuint *p, t_mesh *mesh, t_sdlattr *sdlattr, t_env *a)
{
	int		terminate;
	int		p_index;

	p_index = 0;
	terminate = 0;
	while (!terminate)
	{
		SDL_PollEvent(&sdlattr->events);
		if (sdlattr->events.window.event == SDL_WINDOWEVENT_CLOSE)
			terminate = 1;
		if (sdlattr->events.type == SDL_KEYUP)
			if (sdlattr->events.key.keysym.sym == SDLK_SPACE)
				p_index = bindmatrixglsl(*mesh, a, p_index, p);
		if (sdlattr->events.type == SDL_WINDOWEVENT)
			if (sdlattr->events.window.event == SDL_WINDOWEVENT_RESIZED)
				update_win(a, sdlattr->events.window.data1,
						sdlattr->events.window.data2);
		sdlattr->events.type = 0;
		key_input(mesh, &terminate);
		glUseProgram(p[p_index]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_mesh(*mesh, *a, p_index);
		SDL_GL_SwapWindow(sdlattr->win);
	}
}

int			main(int ac, char **av)
{
	GLuint		programid[2];
	t_mesh		mesh;
	t_sdlattr	sdlattr;
	t_mvp		mvp;
	t_env		a;

	init_sdl();
	init_win(&sdlattr, &a);
	init_opengl();
	mesh = load_model(av[1], ac > 2 ? av[2] : NULL);
	programid[0] = loadshader("colorvertexshader.vertexshader",
			"colorfragmentshader.fragmentshader");
	programid[1] = loadshader("texturevertexshader.vertexshader",
			"texturefragmentshader.fragmentshader");
	mvp.modelmtx[0] = glGetUniformLocation(programid[0], "SCALE");
	mvp.modelmtx[1] = glGetUniformLocation(programid[0], "TRANS");
	mvp.projmtx = glGetUniformLocation(programid[0], "PROJECTION");
	mvp.viewmtx = glGetUniformLocation(programid[0], "VIEW");
	a.loc_lightred = glGetUniformLocation(programid[0], "LIGHTRED");
	a.loc_lightgreen = glGetUniformLocation(programid[0], "LIGHTGREEN");
	a.loc_lightblue = glGetUniformLocation(programid[0], "LIGHTBLUE");
	a.mvp = mvp;
	update_screen(programid, &mesh, &sdlattr, &a);
	dispose(sdlattr);
	return (0);
}
