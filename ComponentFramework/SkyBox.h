#ifndef SKYBOX_H
#define SKYBOX_H

#include <SDL.h>
#include <GL\glew.h>
#include "Shader.h"
#include "SDL_image.h"
#include "ObjLoader.h"

//
#include "Model.h"
#include "Camera.h"
#include "Trackball.h"
#include "SceneEnvironment.h"

namespace GAME {

	class SkyBox : public Model {
	private:
		const char * positive_x_image;
		const char * negative_x_image;
		const char * positive_y_image;
		const char * negative_y_image;
		const char * positive_z_image;
		const char * negative_z_image;
		class Shader *skyBoxShader;
		GLuint textureID;
		GLuint texture;
		GLuint projectionMatrixID;
		GLuint modelViewMatrixID;
		GLuint modelMatrixID;
		GLuint viewMatrixID;
		//ObjLoader obj;


	public:
		SkyBox();
		SkyBox(const char * positive_x_image,
			const char * negative_x_image,
			const char * positive_y_image,
			const char * negative_y_image,
			const char * positive_z_image,
			const char * negative_z_image
			);

		virtual ~SkyBox();


		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float time);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix) const;


	};
}

#endif //!SKYBOX_H