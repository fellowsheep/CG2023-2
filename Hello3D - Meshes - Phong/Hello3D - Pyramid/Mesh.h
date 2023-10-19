#pragma once
class Mesh
{
public:
	Mesh() {}
	~Mesh() {}
	void initialize(/*..*/) {}
	void update(); // atualizar a matriz de transformações
	void draw();
	
	//Métodos getter e setters
	void setPosition(/*..*/);
	//no código principal  objeto1.setShader(&shader);
	//void setShader(Shader* shader) { this->shader = shader;  }


protected:
	//GLuint VAO; //id do buffer de geometria
	//GLuint texID; 


	//informações que compõem a matriz de modelo - model matrix
	//glm::vec position;
	//glm::vec3 dimensions;
	//glm::vec3 angles;

	//Shader* shader;


};

