#pragma once

enum E2DDrawType {
	DRAW_2D_TYPE_TRIANGLE,
	DRAW_2D_TYPE_RECTANGLE,
};

class C2DDraw : public CDummy {
public:
	C2DDraw();
	~C2DDraw();

	EDummyType DummyType() { return EDummyType::DUMMY_TYPE_2DDRAW; }

	virtual E2DDrawType DrawType() = 0;
	virtual void Draw() = 0;

	void DoPulse();
private:
	

};