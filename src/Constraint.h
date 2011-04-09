class Constraint {
public:
	Constraint() {}
	virtual void update(float dt = 0.02) = 0;
	virtual void draw() = 0;
};