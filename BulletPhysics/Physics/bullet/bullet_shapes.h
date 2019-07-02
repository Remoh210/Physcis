#pragma once
#include <Interfaces/iShape.h>
#include <Interfaces/shapes.h>
#include <Interfaces/GL_Vertex.h>
#include <Interfaces/GL_Triangle.h>
#include "btBulletCollisionCommon.h"

namespace nPhysics
{
	
	class cBulletSphereShape : public iSphereShape
	{
	public:
		cBulletSphereShape(float radius);
		virtual ~cBulletSphereShape();
		virtual bool GetSphereRadius(float& radiusOut) { radiusOut = this->mRadius; return true; }
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}
	protected:
		float mRadius;
		btCollisionShape* mBulletShape;
	};

	class cBulletPlaneShape :  public iPlaneShape
	{
	public:
		cBulletPlaneShape(const glm::vec3& normal, float planeConst);
		virtual ~cBulletPlaneShape();
		virtual bool GetPlaneNormal(glm::vec3& planeNormalOut);
		virtual bool GetPlaneConstant(float& planeConstantOut);
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		glm::vec3 mNormal;
		float mCnonst;
		btCollisionShape* mBulletShape;
	};

	class cBulletCylinderShape : public iCylinderShape
	{
	public:
		cBulletCylinderShape(const glm::vec3& halfExtents, int axis);
		virtual ~cBulletCylinderShape();
		virtual float GetCylinderRadius();
		virtual float GetCylinderHeight();
		virtual int GetCylinderAxis();
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		float mRadius;
		int mAxis;
		btCollisionShape* mBulletShape;
	};

	class cBulletCapsuleShape : public iCapsuleShape
	{
	public:
		cBulletCapsuleShape(float height, float radius, int axis);
		virtual ~cBulletCapsuleShape();
		virtual float GetCapsuleRadius();
		virtual float GetCapsuleHeight();
		virtual int GetCapsuleAxis();
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		float mRadius;
		int mAxis;
		float mHeight;
		btCollisionShape* mBulletShape;
	};

	class cBulletBoxShape : public iBoxShape
	{
	public:
		cBulletBoxShape(const glm::vec3& halfExtents);
		virtual ~cBulletBoxShape();
		inline glm::vec3 GetHalfExtents()
		{
			return mHalfExtents;
		};
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		glm::vec3 mHalfExtents;
		btCollisionShape* mBulletShape;
	};

	class cBulletMeshCollider : public iMeshCollider
	{
	public:
		cBulletMeshCollider(const GL_Triangle* triangles, size_t numOfTriangles);
		virtual ~cBulletMeshCollider();
		inline btCollisionShape* GetBulletShape()
		{
			return mBulletShape;
		}

	protected:
		glm::vec3 mHalfExtents;
		btCollisionShape* mBulletShape;
	};

}