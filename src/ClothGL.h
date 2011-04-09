#pragma once
#include "ofMain.h"
#include "Cloth.h"
#include "ofxOpenGL.h"
#include "Particle.h"
#include "Particles.h"

class ClothGL {
public:
	ClothGL(Cloth& rCloth);
	~ClothGL();
	void setup();
	void update();
	void draw();
	void bind();
	void unbind();
	GLuint calcIndex(int nCol, int nRow);
	
	int num_indices;
	int num_vertices;
	GLuint vao_id;
	GLuint vbo_data;
	GLuint vbo_indices;

	
	Cloth& cloth;
	vector<Particle*>& particles;
	VertexPNTTB* vertices;
	GLuint* indices;
	Shader shader;
	Texture tex;
};
