#include "ClothGL.h"
#include <cstdlib>

ClothGL::ClothGL(Cloth& rCloth) 
:cloth(rCloth)
,particles(cloth.particles.particles)
{
	num_vertices = cloth.cols * cloth.rows;
	num_indices = (cloth.cols-1) * (cloth.rows-1) * 4;
	glGenVertexArraysAPPLE(1, &vao_id); eglGetError();
	glGenBuffers(1, &vbo_data);	eglGetError();
	glGenBuffers(1, &vbo_indices); eglGetError();
}

ClothGL::~ClothGL() {
	delete[] vertices;
}

void ClothGL::setup() {
	tex.loadImage("ecoline.png");
	
	glBindVertexArrayAPPLE(vao_id); eglGetError();
	glBindBuffer(GL_ARRAY_BUFFER, vbo_data); eglGetError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices); eglGetError();
	
	shader.load("cloth");
	shader.enable();
	shader.addAttribute("pos").enableVertexAttribArray("pos");
	shader.addAttribute("tex").enableVertexAttribArray("tex");
	shader.addAttribute("norm").enableVertexAttribArray("norm");
	shader.addUniform("tex_diffuse");
	shader.uniform1i("tex_diffuse", 0); // bind to texture_unit 0;	
			
	vertices = new VertexPNTTB[num_vertices];
	
	glBufferData(
		GL_ARRAY_BUFFER
		,num_vertices * sizeof(VertexPNTTB)
		,vertices
		,GL_STREAM_DRAW
	); eglGetError();

	glVertexAttribPointer(
		shader.getAttribute("pos")
		,3
		,GL_FLOAT
		,GL_FALSE
		,sizeof(VertexPNTTB)
		,(GLvoid*)offsetof(VertexPNTTB,pos)
	); eglGetError();

	glVertexAttribPointer(
		shader.getAttribute("tex")
		,2
		,GL_FLOAT
		,GL_FALSE
		,sizeof(VertexPNTTB)
		,(GLvoid*)offsetof(VertexPNTTB,tex)
	); eglGetError();
	
	glVertexAttribPointer(
		shader.getAttribute("norm")
		,3
		,GL_FLOAT
		,GL_FALSE
		,sizeof(VertexPNTTB)
		,(GLvoid*)offsetof(VertexPNTTB,norm)
	); eglGetError();


	indices = new GLuint[num_indices];
	for(int i = 0; i < cloth.cols-1; ++i) {
		for(int j = 0; j < cloth.rows-1; ++j) {
			int dx = ((cloth.cols-1) * j * 4) + i * 4;
			indices[dx] = calcIndex(i,j);
			indices[dx+1] = calcIndex(i+1, j);
			indices[dx+2] = calcIndex(i+1, j+1);
			indices[dx+3] = calcIndex(i,j+1);
		}
	}
	for(int i = 0; i < num_indices; ++i) {
	//	cout << indices[i] << ", ";
	}
	
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER
		,num_indices * sizeof(GLuint)
		,indices
		,GL_STATIC_DRAW
	); eglGetError();
	

	shader.disable();
}

GLuint ClothGL::calcIndex(int nCol, int nRow) {
	GLuint r = (nRow * cloth.cols) + nCol;
	return r;
}

void ClothGL::draw() {
	shader.enable();
	bind();
	
	glActiveTexture(GL_TEXTURE0);
	tex.bind();
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); eglGetError();
	glDrawElements(
		GL_QUADS
		,num_indices
		,GL_UNSIGNED_INT
		,0
	); eglGetError();
	
	tex.unbind();
	unbind();
	shader.disable();
}

void ClothGL::update() {
	for(float i = 0; i < cloth.cols; ++i) {
		for(float j = 0; j < cloth.rows; ++j) {
			Particle& a = cloth.getAt(i,j);
			int dx = (j * cloth.cols) + i;
			vertices[dx].pos = a.pos;
			vertices[dx].tex.set((i/cloth.cols),(j/cloth.rows));
			if(i < cloth.cols - 1 && j < cloth.rows-1 ) {
				Particle& b = cloth.getAt(i+1, j);
				Particle& c = cloth.getAt(i, j+1);
				ofVec3f tan = (b.pos - a.pos).normalize();
				ofVec3f bin = (c.pos - a.pos).normalize();
				//ofVec3f up(0,1,0);
				ofVec3f norm = tan.crossed(bin).normalize();
				//ofVec3f norm = tan.crossed(up).normalize();
				vertices[dx].norm = norm;
				//cout << norm << endl;
				//cout << vertices[dx].norm.x << ", " << vertices[dx].norm.y << endl;
				//cout << norm << " | " << a.pos << " | " << b.pos << endl;
			
			}
		}
	}
	
	// update VBO data
	bind();
	
	glBufferSubData(
		GL_ARRAY_BUFFER
		,0
		,num_vertices * sizeof(VertexPNTTB)
		,&vertices[0]
	); eglGetError();
	unbind();

}

void ClothGL::bind() {
	glBindVertexArrayAPPLE(vao_id); eglGetError();
}

void ClothGL::unbind() {
	glBindVertexArrayAPPLE(0); eglGetError();	
}
