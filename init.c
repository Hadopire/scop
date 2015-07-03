/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/03 14:42:01 by ncharret          #+#    #+#             */
/*   Updated: 2015/07/03 15:06:00 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_sdl(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erreur d'initialisation de la sdl\n");
		SDL_Quit();
		exit(-1);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

void	init_win(t_sdlattr *sdlattr, t_env *a)
{
	a->width = 1366;
	a->height = 768;
	a->ratio = (float)a->width / (float)a->height;
	sdlattr->win = SDL_CreateWindow("Scop OPENGL 4", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, a->width, a->height, SDL_WINDOW_SHOWN
			| SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (sdlattr->win == 0)
	{
		printf("Erreur lors de la creation de la fenetre\n");
		SDL_Quit();
		exit(-1);
	}
	sdlattr->openglcontext = SDL_GL_CreateContext(sdlattr->win);
	if (sdlattr->openglcontext == 0)
	{
		printf("Erreur lors de la creation du contexte opengl\n");
		SDL_DestroyWindow(sdlattr->win);
		SDL_Quit();
		exit(-1);
	}
}

int		bindmatrixglsl(t_mesh mesh, t_env *a, int pid, GLuint *programid)
{
	pid = pid == 1 ? 0 : 1;
	if (mesh.texture.data == NULL)
		pid = 0;
	a->mvp.modelmtx[0] = glGetUniformLocation(programid[pid], "SCALE");
	a->mvp.modelmtx[1] = glGetUniformLocation(programid[pid], "TRANS");
	a->mvp.projmtx = glGetUniformLocation(programid[pid], "PROJECTION");
	a->mvp.viewmtx = glGetUniformLocation(programid[pid], "VIEW");
	return (pid);
}

void	dispose(t_sdlattr sdlattr)
{
	SDL_GL_DeleteContext(sdlattr.openglcontext);
	SDL_DestroyWindow(sdlattr.win);
	SDL_Quit();
}
