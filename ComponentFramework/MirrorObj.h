#ifndef MIRROROBJ_H
#define MIRROROBJ_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "Entity.h"
#include "Model.h"
namespace GAME {

	using namespace MATH;

	class MirrorObj : public Model {

	protected:

		class Shader *shader;

		Matrix4 mirrorMatrix;
		std::vector<Mesh*> meshes;

	public:
		MirrorObj();
		MirrorObj(const Vec3 _pos, const Vec3 _orientation);
		MirrorObj(const  MirrorObj&) = delete;
		MirrorObj(MirrorObj&&) = delete;
		MirrorObj& operator = (const  MirrorObj&) = delete;
		MirrorObj& operator = (MirrorObj&&) = delete;

		virtual ~MirrorObj();
		GLuint textureID;

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