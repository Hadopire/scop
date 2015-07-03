/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncharret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 16:34:06 by ncharret          #+#    #+#             */
/*   Updated: 2015/07/03 15:10:07 by ncharret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include "libft/libft.h"
# include <SDL.h>
# define GL3_PROTOTYPES 1
# include <opengl/gl3.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <strings.h>
# define TAILLE_TAMPON 1024
# define VEC t_vector

typedef float	t_matrix[4][4];
typedef	struct	s_vector
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector;

typedef struct	s_image
{
	int				width;
	int				height;
	unsigned char	*data;
	GLuint			textureid;
}				t_image;

typedef struct	s_mesh
{
	GLfloat		*vtx;
	GLfloat		*colors;
	GLfloat		*uv;
	GLfloat		*normals;
	int			vertex_count;
	t_vector	world_position;
	GLuint		vertexbuffer;
	GLuint		colorbuffer;
	GLuint		uvbuffer;
	GLuint		nmbuffer;
	t_vector	angle;
	float		scale;
	t_image		texture;
}				t_mesh;

typedef struct	s_camconfig
{
	float		ratio;
	float		fov;
	float		near;
	float		far;
}				t_camconfig;

typedef struct	s_objindex
{
	int		cstart;
	int		clen;
	int		vstart;
	int		vlen;
}				t_objindex;

typedef struct	s_sdlattr
{
	SDL_Window		*win;
	SDL_Event		events;
	SDL_GLContext	openglcontext;
}				t_sdlattr;

typedef struct	s_mvp
{
	GLuint		projmtx;
	GLuint		viewmtx;
	GLuint		modelmtx[2];
}				t_mvp;

typedef struct	s_env
{
	int			width;
	int			height;
	float		ratio;
	t_mvp		mvp;
	GLuint		loc_lightred;
	GLuint		loc_lightgreen;
	GLuint		loc_lightblue;
	GLfloat		lightred;
	GLfloat		lightgreen;
	GLfloat		lightblue;
}				t_env;

GLuint			loadshader(const char *fichier_vertex_shader,
								const char *fichier_fragment_shader);
void			create_translation_matrix(t_vector vtc, t_matrix m);
void			print_matrix(t_matrix m);
t_vector		init_vector(float x, float y, float z);
void			print_triangle(GLfloat *vtx, int i);
void			transform_triangle(GLfloat *vtx, t_matrix m, int index);
void			create_rx_matrix(t_matrix m, float angle);
void			create_ry_matrix(t_matrix m, float angle);
void			create_rz_matrix(t_matrix m, float angle);
void			transform_model(GLfloat *vtx, t_matrix m, int triangle);
void			print_model(GLfloat *vtx, int triangle_count);
void			draw_mesh(t_mesh mesh, t_env a, int programid_index);
double			toradian(double angle);
void			create_projection_matrix(t_matrix m, t_camconfig c);
void			create_scale_matrix(t_matrix m, float factor);
void			multiply_matrix(t_matrix result, t_matrix mt1, t_matrix mt2);
t_vector		sub_vector(t_vector a, t_vector b);
double			dot_product(t_vector a, t_vector b);
t_vector		cross_product(t_vector a, t_vector b);
t_vector		norm_vector(t_vector a);
void			create_lookat_matrix(t_matrix m, VEC e, t_vector t, t_vector u);
t_mesh			load_model(char *path, char *imgpath);
void			get_coord_index(char **file, int *vstart, int *vlen);
void			get_vertex_index(char **file, int *vstart, int *vlen, int i);
int				count_obj_vertex(int vstart, int vlen, char **file);
int				count_line_index(char **file, int line);
void			get_index(char **file, int *numb, int i, int linecount);
void			error(char *msg);
char			*read_obj(char *path);
char			**split_obj(char **file);
t_image			load_bmp(char *path);
t_vector		add_vector(t_vector a, t_vector b);
void			key_input(t_mesh *mesh, int *terminate);
void			dispose(t_sdlattr sdlattr);
int				bindmatrixglsl(t_mesh mesh, t_env *a, int pid, GLuint *progr);
void			init_win(t_sdlattr *sdlattr, t_env *a);
void			init_sdl();
void			generate_uv(t_mesh *mesh);
float			compute_average(GLfloat *vtx, int size, int i);
void			center_mesh(t_mesh *mesh);
void			fill_normals(t_mesh *mesh);
#endif
