#include "cBulletPhysicsWorld.h"
#include "nConvert.h"
#include "cBulletRigidBody.h"
#include "cBulletConstraints.h"
#include "BulletCollision/CollisionDispatch/btInternalEdgeUtility.h"


std::pair<std::string, std::string> lastColNames;

extern ContactAddedCallback	gContactAddedCallback;


bool callbackFunc(btManifoldPoint& cp,
	const btCollisionObjectWrapper* obj1, int id1, int index1,
	const btCollisionObjectWrapper* obj2, int id2, int index2)
{
	((nPhysics::cBulletRigidBody*)obj1->getCollisionObject()->getUserPointer())->SetCollision(true);
	((nPhysics::cBulletRigidBody*)obj2->getCollisionObject()->getUserPointer())->SetCollision(true);

	lastColNames.first = ((nPhysics::cBulletRigidBody*)obj1->getCollisionObject()->getUserPointer())->GetGOName();
	lastColNames.second = ((nPhysics::cBulletRigidBody*)obj2->getCollisionObject()->getUserPointer())->GetGOName();
	return false;
}

nPhysics::cBulletPhysicsWorld::cBulletPhysicsWorld()
	: iPhysicsWorld()
{
	mCollisionConfiguration = new btDefaultCollisionConfiguration();

	//default collision dispatcher. 
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

	//general purpose broadphase.
	mOverlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver.
	mSolver = new btSequentialImpulseConstraintSolver();

	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfiguration);

	mDynamicsWorld->setGravity(btVector3(0, -10, 0));

	gContactAddedCallback = callbackFunc;
}

nPhysics::cBulletPhysicsWorld::~cBulletPhysicsWorld()
{
	if (mDynamicsWorld)
	{
		delete mDynamicsWorld;
		mDynamicsWorld = 0;
	}
	if (mSolver)
	{
		delete mSolver;
		mSolver = 0;
	}
	if (mOverlappingPairCache)
	{
		delete mOverlappingPairCache;
		mOverlappingPairCache = 0;
	}
	if (mDispatcher)
	{
		delete mDispatcher;
		mDispatcher = 0;
	}
	if (mCollisionConfiguration)
	{
		delete mCollisionConfiguration;
		mCollisionConfiguration = 0;
	}
}

void nPhysics::cBulletPhysicsWorld::SetGravity(const glm::vec3& gravity)
{
	mDynamicsWorld->setGravity(nConvert::ToBullet(gravity));
}

bool nPhysics::cBulletPhysicsWorld::AddBody(iRigidBody* body)
{

	cBulletRigidBody* bulletRigidBody = dynamic_cast<cBulletRigidBody*>(body);
	if (!bulletRigidBody)
	{
		return false;
	}

	mDynamicsWorld->addRigidBody(bulletRigidBody->GetBulletBody());

	return true;
}

bool nPhysics::cBulletPhysicsWorld::RemoveBody(iRigidBody * body)
{
	cBulletRigidBody* bulletRigidBody = dynamic_cast<cBulletRigidBody*>(body);
	if (!bulletRigidBody)
	{
		return false;
	}
	btRigidBody* BulletBtBody = bulletRigidBody->GetBulletBody();
	mDynamicsWorld->removeRigidBody(BulletBtBody);

	return true;
}

void nPhysics::cBulletPhysicsWorld::AddConstraint(iConstraint * constraint)
{
	eConstraintType type = constraint->GetConstraintType();

	switch (type)
	{
	case nPhysics::CONSTRAINT_TYPE_POINT_TO_POINT:
	{
		cBulletPoinToPointConstraint* basConstraint = dynamic_cast<cBulletPoinToPointConstraint*>(constraint);
		this->mDynamicsWorld->addConstraint(basConstraint->GetTypedConstraint());

	}
	break;
	case nPhysics::CONSTRAINT_TYPE_HINGE:
	{
		cBulletHingeConstraint* hingeConstraint = dynamic_cast<cBulletHingeConstraint*>(constraint);
		this->mDynamicsWorld->addConstraint(hingeConstraint->GetTypedConstraint());
	}
	break;
	default:
		break;
	}
}

void nPhysics::cBulletPhysicsWorld::RemoveConstraint(iConstraint * constraint)
{
}

std::pair<std::string, std::string> nPhysics::cBulletPhysicsWorld::GetLastColPair()
{
	return lastColNames;
}

bool nPhysics::cBulletPhysicsWorld::RayCast(glm::vec3 & from, glm::vec3& to)
{
	btCollisionWorld::ClosestRayResultCallback res(nConvert::ToBullet(from), nConvert::ToBullet(to));
	mDynamicsWorld->rayTest(nConvert::ToBullet(from), nConvert::ToBullet(to), res);
	return res.hasHit();
}

nPhysics::iRigidBody* nPhysics::cBulletPhysicsWorld::RayCastGetObject(glm::vec3 & from, glm::vec3& to)
{
	btCollisionWorld::ClosestRayResultCallback resObject(nConvert::ToBullet(from), nConvert::ToBullet(to));
	mDynamicsWorld->rayTest(nConvert::ToBullet(from), nConvert::ToBullet(to), resObject);
	//Return hit object
	if (resObject.hasHit())
	{
		return static_cast<nPhysics::cBulletRigidBody*>(resObject.m_collisionObject->getUserPointer());
	}

	return NULL;
}

void nPhysics::cBulletPhysicsWorld::Update(float dt)
{
	mDynamicsWorld->stepSimulation(dt, 10);
}
