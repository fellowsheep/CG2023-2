﻿/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico/Computação Gráfica - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 09/08/2023
 *
 */

#include <iostream>
#include <fstream>	
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Classe gerenciadora dos shaders
#include "Shader.h"


// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Protótipos das funções
int setupGeometry();
int loadSimpleOBJ(string filepath, int& nVerts, glm::vec3 color = glm::vec3(1.0,0.0,0.0));

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 1000, HEIGHT = 1000;

bool rotateX=false, rotateY=false, rotateZ=false;

//Variáveis de controle da câmera
glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);

bool firstMouse = true;
float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0; //para calcular o quanto que o mouse deslocou​
float yaw = -90.0, pitch = 0.0; //rotação em x e y​

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola 3D!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	Shader shader("../shaders/HelloPyramid.vs", "../shaders/HelloPyramid.fs");

	// Gerando um buffer simples, com a geometria de um triângulo
	int nVerts;
	GLuint VAO = loadSimpleOBJ("../../3DModels/suzanneTriLowPoly.obj", nVerts);


	glUseProgram(shader.ID);

	//Criando a matriz de modelo
	glm::mat4 model = glm::mat4(1); //matriz identidade;
	model = glm::rotate(model, /*(GLfloat)glfwGetTime()*/glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", glm::value_ptr(model));


	//Criando a matriz de projeção
	glm::mat4 projection = glm::mat4(1); //matriz identidade;
	//projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
	projection = glm::perspective(glm::radians(40.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	shader.setMat4("projection", glm::value_ptr(projection));

	//Criando a matriz de view
	glm::mat4 view = glm::mat4(1);
	view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), cameraUp);
	shader.setMat4("view", glm::value_ptr(view));

	glEnable(GL_DEPTH_TEST);


	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		float angle = (GLfloat)glfwGetTime();

		model = glm::mat4(1);

		float offset = cos((GLfloat)glfwGetTime());
		//model = glm::translate(model, glm::vec3(0.0, 0.0, offset));

		if (rotateX)
		{
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));

		}
		else if (rotateY)
		{
			model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));

		}
		else if (rotateZ)
		{
			model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		}

		shader.setMat4("model", glm::value_ptr(model));

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", glm::value_ptr(view));
		
		// Chamada de desenho - drawcall
		// Poligono Preenchido - GL_TRIANGLES
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, nVerts);

		// Chamada de desenho - drawcall
		// CONTORNO - GL_LINE_LOOP
		// VERTICES - GL_POINTS
		
		//glDrawArrays(GL_POINTS, 0, 18);
		glBindVertexArray(0);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		rotateX = true;
		rotateY = false;
		rotateZ = false;
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		rotateX = false;
		rotateY = true;
		rotateZ = false;
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		rotateX = false;
		rotateY = false;
		rotateZ = true;
	}

	float cameraSpeed = 0.05;

	if (key == GLFW_KEY_W)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (key == GLFW_KEY_S)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
	{
		cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront,cameraUp));
	}
	if (key == GLFW_KEY_D)
	{
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	}



}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLfloat vertices[] = {

		//Base da pirâmide: 2 triângulos
		//x    y    z    r    g    b
		-0.5, -0.5, -0.5, 1.0, 1.0, 0.0, // v0
		-0.5, -0.5,  0.5, 0.0, 1.0, 1.0, // v1
		 0.5, -0.5, -0.5, 1.0, 0.0, 1.0, // v2

		 -0.5, -0.5, 0.5, 1.0, 1.0, 0.0, //v3
		  0.5, -0.5, 0.5, 0.0, 1.0, 1.0, //v4 
		  0.5, -0.5,-0.5, 1.0, 0.0, 1.0, //v5

		 // Primeiro triângulo (amarelo)
		 -0.5, -0.5, -0.5, 1.0, 1.0, 0.0, //v6
		  0.0,  0.5,  0.0, 1.0, 1.0, 0.0, //v7
		  0.5, -0.5, -0.5, 1.0, 1.0, 0.0, //v8

		  // Segundo triângulo (magenta)
		  -0.5, -0.5, -0.5, 1.0, 0.0, 1.0, //v9
		   0.0,  0.5,  0.0, 1.0, 0.0, 1.0, //v10
		  -0.5, -0.5,  0.5, 1.0, 0.0, 1.0, //v11

		  // Terceiro triângulo (amarelo)
		  -0.5, -0.5, 0.5, 1.0, 1.0, 0.0, //v12
		   0.0,  0.5, 0.0, 1.0, 1.0, 0.0, //v13
		   0.5, -0.5, 0.5, 1.0, 1.0, 0.0, //v14

		   // Quarto triângulo (ciano)
		   0.5, -0.5,  0.5, 0.0, 1.0, 1.0, //v15
		   0.0,  0.5,  0.0, 0.0, 1.0, 1.0, //v16
		   0.5, -0.5, -0.5, 0.0, 1.0, 1.0, //v17
	};

	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);

	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);

	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	
	//Atributo posição (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//cout << xpos << "\t" << ypos << endl;

	if (firstMouse)

	{

		lastX = xpos;

		lastY = ypos;

		firstMouse = false;

	}



	float xoffset = xpos - lastX;

	float yoffset = lastY - ypos;

	lastX = xpos;

	lastY = ypos;



	float sensitivity = 0.05;

	xoffset *= sensitivity;

	yoffset *= sensitivity;


	yaw += xoffset;

	pitch += yoffset;



	if (pitch > 89.0f)

		pitch = 89.0f;

	if (pitch < -89.0f)

		pitch = -89.0f;



	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));

	front.y = sin(glm::radians(pitch));

	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(front);



	//Precisamos também atualizar o cameraUp!! Pra isso, usamos o Up do  

	//mundo (y), recalculamos Right e depois o Up

	glm::vec3 right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));

	cameraUp = glm::normalize(glm::cross(right, cameraFront));

}

int loadSimpleOBJ(string filepath, int& nVerts, glm::vec3 color)
{
	//vector em que estaremos armazenando o buffer de geometria
	vector <GLfloat> vbuffer;
	//vectors auxiliares na leitura    
	vector <glm::vec3> vertices;
	vector <glm::vec3> normals;
	vector <glm::vec2> texcoords;

	//stream de leitura de arquivo em C++    
	ifstream inputFile;
	inputFile.open(filepath.c_str());

	if (inputFile.is_open())
	{
		char line[100];
		string sline;
		while (!inputFile.eof())
		{
			inputFile.getline(line, 100);
			sline = line;
			string word;

			istringstream ssline(line);
			ssline >> word;
			if (word == "v")
			{
				glm::vec3 v;
				ssline >> v.x >> v.y >> v.z;
				vertices.push_back(v);
			}
			if (word == "f")
			{
				string tokens[3];
				ssline >> tokens[0] >> tokens[1] >> tokens[2];
				for (int i = 0; i < 3; i++)
				{
					int pos = tokens[i].find("/");
					string token = tokens[i].substr(0, pos);

					int index = atoi(token.c_str()) - 1;


					vbuffer.push_back(vertices[index].x);
					vbuffer.push_back(vertices[index].y);
					vbuffer.push_back(vertices[index].z);

					vbuffer.push_back(rand() % 256 / 255.0);
					vbuffer.push_back(rand() % 256 / 255.0);
					vbuffer.push_back(rand() % 256 / 255.0);
				}
			}
		}
	}
	else
	{
		cout << "Problema ao encontrar o arquivo " << filepath << endl;
	}
	inputFile.close();
	GLuint VBO, VAO;

	nVerts = vbuffer.size() / 6; //Provisório    

	//Geração do identificador do VBO   

	glGenBuffers(1, &VBO);    //Faz a conexão (vincula) do buffer como um buffer de array    
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Envia os dados do array de floats para o buffer da OpenGl    
	glBufferData(GL_ARRAY_BUFFER, vbuffer.size() * sizeof(GLfloat), vbuffer.data(), GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)    
	glGenVertexArrays(1, &VAO);    // Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices    
	// e os ponteiros para os atributos     

	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando:     // Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)    // Numero de valores que o atributo tem (por ex, 3 coordenadas xyz)     // Tipo do dado    // Se está normalizado (entre zero e um)    // Tamanho em bytes     // Deslocamento a partir do byte zero     //Atributo posição (x, y, z)    
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor (r, g, b)    
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);    // Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice     // atualmente vinculado - para que depois possamos desvincular com segurança    
	glBindBuffer(GL_ARRAY_BUFFER, 0);  // Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)    
	glBindVertexArray(0);

	return VAO;
}



