#pragma once
class Mesh
{
public:
	Mesh() {}
	~Mesh() {}
	void initialize(/*..*/) {}
	void update(); // atualizar a matriz de transforma��es
	void draw();
	
	//M�todos getter e setters
	void setPosition(/*..*/);
	//no c�digo principal  objeto1.setShader(&shader);
	//void setShader(Shader* shader) { this->shader = shader;  }


protected:
	//GLuint VAO; //id do buffer de geometria
	//GLuint texID; 


	//informa��es que comp�em a matriz de modelo - model matrix
	//glm::vec position;
	//glm::vec3 dimensions;
	//glm::vec3 angles;

	//Shader* shader;


};

