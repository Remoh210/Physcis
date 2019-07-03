#include <Interfaces/iPhysicsFactory.h>
#include <Interfaces/iRigidBody.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <glm/vec3.hpp>
#include <vector>


HINSTANCE hGetProckDll = 0;
//Pointer to the function
typedef nPhysics::iPhysicsFactory*(*f_createPhysicsFactory)();

int main()
{
	hGetProckDll = LoadLibraryA("BulletPhysics.dll");

	f_createPhysicsFactory CreatePhysicsFactory =
		(f_createPhysicsFactory)GetProcAddress(hGetProckDll, "CreateFactory");

	nPhysics::iPhysicsFactory* physicsFactory = CreatePhysicsFactory();
	nPhysics::iPhysicsWorld* physicsWorld = physicsFactory->CreatePhysicsWorld();
	
	physicsWorld->SetGravity(glm::vec3(0.f, -10.f, 0.f));

	nPhysics::sRigidBodyDef def;
	def.Position = glm::vec3(0.f, 0.f, 0.f);
	def.Mass = 20.f;
	def.Orientation = glm::vec3(0.f, 0.f, 0.f);

	nPhysics::iBoxShape* BoxShape = physicsFactory->CreateBoxShape(glm::vec3(10.f, 5.f, 10.f));
	nPhysics::iRigidBody* RigidBody = physicsFactory->CreateRigidBody(def, BoxShape);
	physicsWorld->AddBody(RigidBody);

	while (true)
	{
		float dt = 0.f;
		physicsWorld->Update(dt);
	}

}