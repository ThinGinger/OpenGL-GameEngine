#include "FireObj.h"
#include "Perlin.h"
namespace GAME {


	FireObj::FireObj()
	{

	}

	FireObj::FireObj(const Vec3 pos_, const Vec3 orientation_)
	{
		pos = pos_;
		orientation = orientation_;
		shader = nullptr;
	}

	FireObj::~FireObj()
	{
		OnDestroy();
	}

	void FireObj::setPos(const Vec3 & pos_)
	{
		Model::setPos(pos_);
		updatemodelMatrix();
	}

	void FireObj::setOrientation(const Vec3 & orientation_)
	{
		Model::setOrientation(orientation_);
		updatemodelMatrix();
	}
	void FireObj::updatemodelMatrix()
	{
		modelMatrix = MMath::translate(pos);
	}

	bool FireObj::OnCreate()
	{
		//shader = new Shader("textureVert.glsl", "textureFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
		Perlin perlin;
		tNoise = perlin.CreateNoise3D();
		elapsedTime = 0;

		shader = new Shader("reflectionVert.glsl", "reflectionFrag.glsl", 2, 0, "vVertex", 1, "vNormal", "texCoords");

		return true;
	}

	bool FireObj::LoadMesh(const char * filename)
	{
		if (ObjLoader::loadOBJ(filename) == false) {
			return false;
		}
		/// Get the data out of the ObjLoader and into our own mesh
		meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));
		return true;
	}
	void FireObj::Update(const float deltaTime)
	{
		elapsedTime += deltaTime;
		std::cout << elapsedTime << std::endl;
	}


	void FireObj::Render() const
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		GLint projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
		/// GLint viewMatrixID = glGetUniformLocation(shader->getProgram(), "viewMatrix");
		/// GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
		GLint modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
		GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
		GLint lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
		GLuint noiseID = glGetUniformLocation(shader->getProgram(), "tNoise");
		GLuint elapsedTimeID = glGetUniformLocation(shader->getProgram(), "elapsedTime");


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


		glUniform1f(elapsedTimeID, elapsedTime);
		glUniform1i(noiseID, tNoise);

		for (Mesh* mesh : meshes) {
			mesh->Render();
		}


	}

	void FireObj::OnDestroy()
	{
		if (shader) delete shader;
	}






}

