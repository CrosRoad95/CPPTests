#pragma once

enum EDummyType {
	DUMMY_TYPE_2DDRAW,
	DUMMY_TYPE_ENTITY,
};

class CDummy {

public:

	CDummy();
	~CDummy();

	virtual EDummyType DummyType() = 0;

	virtual void DoPulse() = 0;
	void DoDummyPulse();
	void Do1SecPulse();
};