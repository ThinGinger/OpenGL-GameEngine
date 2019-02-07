#pragma once
#ifndef FIREOBJ_H
#define FIREOBJ_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Entity.h"
#include "Model.h"
#include "Timer.h"
namespace GAME {

	using namespace MATH;

	class FireObj : public Model {

	protected:

		class Shader *shader;
		std::vector<Mesh*> meshes;
		Timer timer;
		float elapsedTime;

	public:
		FireObj();
		FireObj(const Vec3 _pos, const Vec3 _orientation);
		FireObj(const  FireObj&) = delete;
		FireObj(FireObj&&) = delete;
		FireObj& operator = (const  FireObj&) = delete;
		FireObj& operator = (FireObj&&) = delete;

		virtual ~FireObj();
		GLuint textureID;
		GLuint noiseID;
		GLuint tNoise;
		void setPos(const Vec3& pos_) override;
		void setOrientation(const Vec3& orientation_) override;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Render() const;
		virtual void Update(const float deltaTime);
		//virtual void updateModelMatrix();

		virtual bool LoadMesh(const char* filename);

	protected:

		void updatemodelMatrix();
	};
} /// end of namespace

#endif