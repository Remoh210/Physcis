#pragma once
#include "iRigidBody.h"
#include "eConstraintType.h"

namespace nPhysics
{
	class iConstraint
	{
	public:
		virtual ~iConstraint() {}

		inline eConstraintType GetConstraintType() const { return mConstraintType; }

	protected:
		// The constructor is protector, only accessible by the subclasses
		iConstraint(eConstraintType constraintType) : mConstraintType(constraintType) {}
		iConstraint() {}
	private:
		eConstraintType mConstraintType;
	};
}