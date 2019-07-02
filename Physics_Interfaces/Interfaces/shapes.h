#pragma once
#include "iShape.h"
#include <glm/glm.hpp>

namespace nPhysics
{
	class iSphereShape : public iShape
	{
	public:
		virtual ~iSphereShape() {}
		virtual bool GetSphereRadius(float& radiusOut) = 0;

	protected:
		iSphereShape() : iShape(SHAPE_TYPE_SPHERE) {}
	};

	class iPlaneShape : public iShape
	{
	public:
		virtual ~iPlaneShape() {}
		virtual bool GetPlaneConstant(float& planeConstantOut) = 0;
		virtual bool GetPlaneNormal(glm::vec3& planeNormalOut) = 0;

	protected:
		iPlaneShape() : iShape(SHAPE_TYPE_PLANE) {}
	};

	class iCylinderShape : public iShape
	{
	public:
		virtual ~iCylinderShape() {}
		virtual float GetCylinderRadius() = 0;
		virtual float GetCylinderHeight() = 0;
		virtual int GetCylinderAxis() = 0;

	protected:
		iCylinderShape() : iShape(SHAPE_TYPE_CYLINDER) {}
	};

	class iCapsuleShape : public iShape
	{
	public:
		virtual ~iCapsuleShape() {}
		virtual float GetCapsuleRadius() = 0;
		virtual float GetCapsuleHeight() = 0;
		virtual int GetCapsuleAxis() = 0;

	protected:
		iCapsuleShape() : iShape(SHAPE_TYPE_CAPSULE) {}
	};

	class iBoxShape : public iShape
	{
	public:
		virtual ~iBoxShape() {}
		virtual glm::vec3 GetHalfExtents() = 0;


	protected:
		iBoxShape() : iShape(SHAPE_TYPE_BOX) {}
	};

	class iMeshCollider : public iShape
	{
	public:
		virtual ~iMeshCollider() {}

	protected:
		iMeshCollider() : iShape(SHAPE_TYPE_MESH) {}
	};
}