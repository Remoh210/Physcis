#pragma once
#include <Interfaces/iPhysicsWorld.h>
#include "btBulletDynamicsCommon.h"
#include <stdio.h>
#include <string>

namespace nPhysics {
	class cBulletPhysicsWorld : public iPhysicsWorld
	{
	public:
		cBulletPhysicsWorld();
		~cBulletPhysicsWorld();

		void SetGravity(const glm::vec3& gravity);

		bool AddBody(iRigidBody* body);
		bool RemoveBody(iRigidBody* body);

		//Constraints
		virtual void AddConstraint(iConstraint* constraint);
		virtual void RemoveConstraint(iConstraint* constraint);

		//Collision
		virtual std::pair<std::string, std::string> GetLastColPair();
		virtual bool RayCast(glm::vec3& from, glm::vec3& to);
		virtual iRigidBody* RayCastGetObject(glm::vec3& from, glm::vec3& to);
		void Update(float dt);

	private:

		btDefaultCollisionConfiguration* mCollisionConfiguration;

		//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher 
		btCollisionDispatcher* mDispatcher;

		//btDbvtBroadphase is a good general purpose broadphase. 
		btBroadphaseInterface* mOverlappingPairCache;

		//the default constraint solver. For parallel processing you can use a different solver 
		btSequentialImpulseConstraintSolver* mSolver;

		btDiscreteDynamicsWorld* mDynamicsWorld;

	};

}