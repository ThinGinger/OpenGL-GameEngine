#include "MirrorObj.h"

namespace GAME {





	MirrorObj::MirrorObj()
	{
	}

	MirrorObj::MirrorObj(const Vec3 pos_, const Vec3 orientation_)
	{
		pos = pos_;
		orientation = orientation_;
		shader = nullptr;
	}

	MirrorObj::~MirrorObj()
	{
		OnDestroy();
	}

	void MirrorObj::setPos(const Vec3 & pos_)
	{
		Model::setPos(pos_);
		updatemodelMatrix();
	}

	void MirrorObj::setOrientation(const Vec3 & orientation_)
	{
		Model::setOrientation(orientation_);
		updatemodelMatrix();
	}
	void MirrorObj::updatemodelMatrix()
	{
		modelMatrix = MMath::translate(pos);
	}

	bool MirrorObj::OnCreate()
	{
		shader = new Shader("reflectionVert.glsl", "reflectionFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
		//shader = new Shader("toonVert.glsl", "toonFrag.glsl", 2, 0, "vVertex", 1, "vNormal");



		IMG_Init(IMG_INIT_JPG);
		SDL_Surface* image = IMG_Load("skull_texture.jpg");


		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



		return true;
	}

	bool MirrorObj::LoadMesh(const char * filename)
	{
		if (ObjLoader::loadOBJ(filename) == false) {
			return false;
		}
		/// Get the data out of the ObjLoader and into our own mesh
		meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));
		return true;
	}
	void MirrorObj::Update(const float deltaTime)
	{
	}
	

	void MirrorObj::Render() const
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		GLint projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
		/// GLint viewMatrixID = glGetUniformLocation(shader->getProgram(), "viewMatrix");
		/// GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
		GLint modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
		GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
		GLint lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");

		glUseProgram(shader->getProgram());
		/// glBindTexture(GL_TEXTURE_2D, textureID);

		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, Camera::currentCamera->getProjectionMatrix());
		/// glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, Camera::currentCamera->getViewMatrix());
		/// glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix * Trackball::getInstance()->getMatrix4());
		glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, Camera::currentCamera->getViewMatrix() *
			(modelMatrix * Trackball::getInstance()->getMatrix4()));

		/// Assigning the 4x4 modelMatrix to the 3x3 normalMatrix 
		/// copies just the upper 3x3 of the modelMatrix
		Matrix3 normalMatrix = modelMatrix * Trackball::getInstance()->getMatrix4();
		glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);

		glUniform3fv(lightPosID, 1, SceneEnvironment::getInstance()->getLight());

		for (Mesh* mesh : meshes) {
			mesh->Render();
		}


	}
	
void MirrorObj::OnDestroy()
	{
		if (shader) delete shader;
	}
	

	

	

}

