class CRectangle : public C2DDraw {
public:
	CRectangle(Vertex2D* position, uint width, uint heigth, ColorRGBA* color);
	~CRectangle();
	void Draw();

	E2DDrawType DrawType() { return E2DDrawType::DRAW_2D_TYPE_RECTANGLE; }

private:
	Vertex2D* vPosition;
	uint uiWidth;
	uint uiHeigth;
	ColorRGBA* cColor;
};