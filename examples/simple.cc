#include "engine.h"
#include "math.h"

typedef size_t enty;

Engine engine;
Mesh mesh;
enty obj;

struct Jam: Game
{
	void start();
	Mat4 update(Input, double, double);
};

void Jam::start()
{
	size_t tetra = engine.add_mesh(&mesh);
	obj = engine.add_entity(tetra);
}

Mat4 Jam::update(Input input, double time, double delta)
{
	Instance instance;
	instance.color = Color { 1, 0.5f, 0.3f };
	instance.model = Mat4::translation(0, -0.25f, 1.5f)
		* Mat4::rotation_y(time);
	engine.update_entity(obj, instance);
	return Mat4::id();
}

int main()
{
	float alt = sqrt(3) * 0.5f;
	float apo = alt / 3;
	float rad = alt - apo;

	float proj = sqrt(alt * alt - apo * apo);
	float low = proj * 0.25;
	float up = 3 * low;

	float pos[] = {
		 0.0, -low,  rad,
		 0.5, -low, -apo,
		-0.5, -low, -apo,

		 0.0, -low,  rad,
		 0.5, -low, -apo,
		-0.5, -low, -apo,

		 0.0, up, 0.0 // Peak
	};

	unsigned int ind[] = {
		0, 2, 1,
		3, 4, 6,
		4, 5, 6,
		5, 3, 6
	};

	Vertex vert[7];
	mesh = Mesh(vert, 7, pos, ind, 12);

	Jam jam;
	engine.init(jam);
}