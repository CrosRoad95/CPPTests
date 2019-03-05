#include "StdInc.h"

CDummy::CDummy(){
	pGame->GetWorld()->RegisterDummy(this);
};

CDummy::~CDummy() {
	pGame->GetWorld()->UnregisterDummy(this);
};

void CDummy::DoDummyPulse() {

	EDummyType EType = DummyType();
	switch (EType)
	{
	case DUMMY_TYPE_2DDRAW:
		DoPulse();
		break;
	case DUMMY_TYPE_ENTITY:
		DoPulse();
		break;

	default:
		break;
	}
};

void CDummy::Do1SecPulse() {
	EDummyType EType = DummyType();
	switch (EType)
	{
		case DUMMY_TYPE_2DDRAW:
			break;
		default:
			break;
	}
};
