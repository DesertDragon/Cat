ENUM( Color, Red, Green, Blue );

struct Cat
{
	//const char* getName(){ return name; }
	//Color getRightEye(){ return rightEye; }
	//Color getLeftEye(){ return leftEye; }
private:
	const char* name;  SELF VIEW(name);
	Color leftEye  = Blue;  VIEW(leftEye);
	Color rightEye /*= Green*/; VIEW(rightEye);
public:
	Cat(const char* name): name(name) {}
	//void show(ostream& out) override;
};
