#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <AntTweakBar.h>
#include "Scene.h"
#include "AssimpSceneImporter.h"
#include <Commdlg.h>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "framebuffer.h"

int windowWidth = 800;
int windowHeight = 600;

float myVar;
TwBar *gGUI_MaterialBar;

Scene gScene;
int gSelectedMaterial = -1;

float cameraDist = 100.0;
float cameraAngle1 = -1.57;
float cameraAngle2 = 0.0;
float g_EyeDistance = 6.2;

bool useFrustum = false;

int lastMouseX = -1;
int lastMouseY = -1;

int mouseActionState = 0; //0: nothing, 1: rotate around, 2: zoom

Shader* g_SceneMaterialShader;
Mesh*   g_FullscreenQuad;
Shader* g_FullscreenQuadShader;

Framebuffer* g_LeftEyeImage;
Framebuffer* g_RightEyeImage;


enum AnaglyphMode
{
	AM_RED_BLUE,
	AM_RED_CYAN,
	AM_COLOR,
	AM_HALFCOLOR,
	AM_OPTIMIZED,
	AM_DUBOIS,
};


unsigned int AnaglyphModeCount = 6;
AnaglyphMode g_AnaglyphMode = AM_RED_BLUE;
TwEnumVal AnaglyphModeEV[] = {	{ AM_RED_BLUE, "Red Blue" },{ AM_RED_CYAN, "Red Cyan" },{ AM_COLOR, "Color" },
								{ AM_HALFCOLOR, "Halfcolor" },{ AM_OPTIMIZED, "Opptimized" },{ AM_DUBOIS, "Dubois" } };
TwType AnaglyphModeType;

void attachGUIToMaterials();
void attachGUIToMaterial(Material& mat);
void TW_CALL materialSelected(void* clientData);


void renderFSQuad()
{
	glDepthMask(false);
	glDisable(GL_DEPTH_TEST);
	g_FullscreenQuad->render();
	glEnable(GL_DEPTH_TEST);
	glDepthMask(true);
}

void display()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projMat;
	//projMat = glm::perspectiveFov(60.0f, (float)windowWidth, (float)windowHeight, 0.1f, 1000.0f);
	projMat = glm::perspective(21.83f, 16.0f / 9.0f, 0.1f, 1000.0f);
	
	Vector3 camPos(cos(cameraAngle1), 0, -sin(cameraAngle1)); 
	camPos.y = sin(cameraAngle2) * camPos.length();
	camPos.normalize();
	camPos = camPos * cameraDist;	
	glm::mat4 viewMat = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(0,0,0),glm::vec3(0,1,0));
	
	/*g_SceneMaterialShader->enable();
	g_SceneMaterialShader->bindUniformMat4("projection_matrix", &projMat[0][0]);
	g_SceneMaterialShader->bindUniformMat4("view_matrix", &viewMat[0][0]);
	glm::mat4 viewIT = glm::transpose(glm::inverse(viewMat));
	g_SceneMaterialShader->bindUniformMat4("viewIT_matrix", &viewIT[0][0]);
	
	gScene.renderScene(g_SceneMaterialShader);*/

	viewMat[3][0] += 0.5;

	float n = 0.1f;
	float f = 200.0f;
	float w = 48.0f;
	float h = 27.0f;
	float s = g_EyeDistance / 2.0f;
	float d = 70.0f;

	g_SceneMaterialShader->enable();
	//glColorMask(false, false, true, false);
	g_RightEyeImage->setRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(useFrustum)
	{
		glm::mat4 projMatR = glm::frustum(-n * (w / 2.0f + s) / d,
			n * (w / 2.0f - s) / d,
			-(n * h / 2.0f) / d,
			(n * h / 2.0f) / d,
			n, f);
		g_SceneMaterialShader->bindUniformMat4("projection_matrix", &projMatR[0][0]);
	}else
		g_SceneMaterialShader->bindUniformMat4("projection_matrix", &projMat[0][0]);
	glm::mat4 viewMatR = viewMat;
	viewMatR[3][0] -= g_EyeDistance * 0.5;
	g_SceneMaterialShader->bindUniformMat4("view_matrix", &viewMatR[0][0]);
	glm::mat4 viewMatR_IT = glm::transpose(glm::inverse(viewMatR));
	g_SceneMaterialShader->bindUniformMat4("viewIT_matrix", &viewMatR_IT[0][0]);
	gScene.renderScene(g_SceneMaterialShader);
	g_RightEyeImage->disableRenderTarget();


	//glColorMask(true, false, false, false);
	//glClear(GL_DEPTH_BUFFER_BIT);
	g_LeftEyeImage->setRenderTarget();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (useFrustum)
	{
		glm::mat4 projMatL = glm::frustum(-n * (w / 2.0f - s) / d,
			n * (w / 2.0f + s) / d,
			-(n * h / 2.0f) / d,
			(n * h / 2.0f) / d,
			n, f);
		g_SceneMaterialShader->bindUniformMat4("projection_matrix", &projMatL[0][0]);
	}
	else
		g_SceneMaterialShader->bindUniformMat4("projection_matrix", &projMat[0][0]);
	glm::mat4 viewMatL = viewMat;
	viewMatL[3][0] += 0.5;
	g_SceneMaterialShader->bindUniformMat4("view_matrix", &viewMatL[0][0]);
	glm::mat4 viewMatL_IT = glm::transpose(glm::inverse(viewMatL));
	g_SceneMaterialShader->bindUniformMat4("viewIT_matrix", &viewMatL_IT[0][0]);
	gScene.renderScene(g_SceneMaterialShader);
	//glColorMask(true, true, true, true);
	g_LeftEyeImage->disableRenderTarget();



	g_SceneMaterialShader->disable();
		

	g_FullscreenQuadShader->enable();
	g_FullscreenQuadShader->bindUniformTexture("l_texture", g_LeftEyeImage->getTextureHandle());
	g_FullscreenQuadShader->bindUniformTexture("r_texture", g_RightEyeImage->getTextureHandle());
	g_FullscreenQuadShader->bindUniformInt("anaglyphMode", g_AnaglyphMode);
	renderFSQuad();
	g_FullscreenQuadShader->disable();


	TwDraw();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}



void initOpenGL()
{
	glewInit();
	
	//glClearColor(0.5,0.5,0.5,1.0);
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	const GLchar* inAttributes[4];
	inAttributes[0] = "position";
	inAttributes[1] = "normal";
	inAttributes[2] = "texCoord";
	inAttributes[3] = "tangents";
	Shader::Values inAttributesV(inAttributes, 4);
	g_SceneMaterialShader = new Shader("SceneMaterial.v", "SceneMaterial.f", inAttributesV);

	Vector3 positions[] = { Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(1,1,0),Vector3(-1,1,0) };
	unsigned short indices[] = { 0,1,2,0,2,3 };
	g_FullscreenQuad = new Mesh();
	g_FullscreenQuad->setData(&positions[0].x, indices, 4, 2);
	Shader::Values inAttributesFSQuad(inAttributes, 1);
	g_FullscreenQuadShader = new Shader("FSQuad.v", "FSQuad.f", inAttributesFSQuad);

	gScene.initGL();

	AssimpSceneImporter::loadMeshToScene("sphere.obj", &gScene);

	g_LeftEyeImage = new Framebuffer(800, 600, false, true);
	g_RightEyeImage = new Framebuffer(800, 600, false, true);

}

void TW_CALL loadScene(void* clientData)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwnd = GetForegroundWindow();              // owner window
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Wavefront OBJ\0*.obj\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE)
	{
		gScene.clearScene();
		AssimpSceneImporter::loadMeshToScene(ofn.lpstrFile, &gScene);		
		materialSelected(0);
	}
}
void TW_CALL toggleFullscreen(void* clientData)
{
	glutFullScreenToggle();
}
void TW_CALL saveMaterials(void* clientData)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwnd = GetForegroundWindow();              // owner window
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0OBJ material\0*.mtl\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE)
	{
		std::ofstream oFile(ofn.lpstrFile);

		for(int i = -1; i < (int) gScene.mMaterials.size(); ++i)
		{
			Material* mat = 0;
			if(i == -1)
				mat = &gScene.getDefaultMaterial();
			else
				mat = gScene.mMaterials[i];
			oFile << "newmtl " << mat->name << std::endl;
			oFile << "Kd " << mat->surfaceColor.x << " " << mat->surfaceColor.y << " " << mat->surfaceColor.z << std::endl;
			if(mat->colorTexName != 0)
				oFile << "map_Kd " << mat->colorTexName << std::endl;
			if(mat->normalTexName != 0)
				oFile << "map_Ka " << mat->normalTexName << std::endl;
		}
		oFile.close();		
	}
}

void TW_CALL loadMaterial(void* clientData)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwnd = GetForegroundWindow();              // owner window
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0OBJ material\0*.mtl\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE)
	{
		Material* mat = 0;
		if(gScene.mMaterials.size() == 0)
			mat = &gScene.getDefaultMaterial();
		else
			mat = gScene.mMaterials[gSelectedMaterial];	

		if(mat->colorTexName) {delete mat->colorTexName; mat->colorTexName = 0;}
		if(mat->normalTexName) {delete mat->normalTexName; mat->normalTexName = 0;}
		
		std::ifstream iFile(ofn.lpstrFile);

		std::string line;
		while(std::getline(iFile, line))
		{
			std::stringstream ss(line);
			string token;
			ss >> token;
			
			if(token.compare("Kd") == 0)
			{
				ss >> mat->surfaceColor.x >> mat->surfaceColor.y >> mat->surfaceColor.z;
			}
			else if(token.compare("map_Kd") == 0 )
			{
				ss >> token;
				mat->colorTexName = new char[token.size()+1];
				token.copy(mat->colorTexName, token.size(), 0);
				mat->colorTexName[token.size()] = '\0';
			}
			else if(token.compare("map_Ka") == 0 )
			{
				ss >> token;
				mat->normalTexName = new char[token.size()+1];
				token.copy(mat->normalTexName, token.size(), 0);
				mat->normalTexName[token.size()] = '\0';
			}
		}
		mat->init();
		materialSelected((void*) gSelectedMaterial);
	}
}

void initGUI()
{
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(windowWidth, windowHeight);
	
	gGUI_MaterialBar = TwNewBar("Material");
	
	materialSelected(0);

	TwBar* fileBar = TwNewBar("File");
	TwAddButton(fileBar, "Open Scene File", (TwButtonCallback)loadScene, NULL,"");
	TwAddButton(fileBar, "Load Material to selected", (TwButtonCallback) loadMaterial, NULL,"");
	TwAddButton(fileBar, "Save Materials", (TwButtonCallback)saveMaterials, NULL,"");
	TwAddSeparator(fileBar, "Separator", "");
	TwAddButton(fileBar, "Toggle Fullscreen", (TwButtonCallback)toggleFullscreen, NULL, "");
	TwAddVarRW(fileBar, "Eye Distance", TW_TYPE_FLOAT, &g_EyeDistance, "min=-10.0 max=10.0 step = 0.01");
	AnaglyphModeType = TwDefineEnum("AnaglyphModeType", AnaglyphModeEV, AnaglyphModeCount);
	TwAddVarRW(fileBar, "Use frustum", TW_TYPE_BOOLCPP, &useFrustum, NULL);
	TwAddVarRW(fileBar, "Anaglyph Mode", AnaglyphModeType, &g_AnaglyphMode, NULL);
	TwDefine(" File size='200 120' position='20 400'"); // change default tweak bar size and color
	
	TwGLUTModifiersFunc(glutGetModifiers);
}

void TW_CALL materialSelected(void* clientData)
{
	unsigned int materialID = (unsigned int) clientData;
	gSelectedMaterial = materialID;
	TwRemoveAllVars(gGUI_MaterialBar);
	attachGUIToMaterials();
	if(gScene.mMaterials.size() <= materialID)
		attachGUIToMaterial(gScene.getDefaultMaterial());
	else
		attachGUIToMaterial(*gScene.mMaterials[materialID]);
}

void attachGUIToMaterials()
{
	for(int i = 0; i < gScene.mMaterials.size();++i)
	{
		TwAddButton(gGUI_MaterialBar, gScene.mMaterials[i]->name, (TwButtonCallback) materialSelected, (void*) i, "group = SceneMaterials");		
	}
}

void attachGUIToMaterial(Material& mat)
{
	float zero = 0;
	float one = 1;
	float step = 0.01;
	
	if(mat.colorTexName == 0)
		TwAddVarRW(gGUI_MaterialBar, "SurfaceColor", TW_TYPE_COLOR3F, &mat.surfaceColor.x, " colormode=rgb group=Properties");
	else
		TwAddVarRO(gGUI_MaterialBar, "ColorTexture", TW_TYPE_CSSTRING(sizeof(mat.colorTexName)), mat.colorTexName, " group=Properties");

	if(mat.normalTexName)
		TwAddVarRO(gGUI_MaterialBar, "NormalTexture", TW_TYPE_CSSTRING(sizeof(mat.normalTexName)), mat.normalTexName, " group=Properties");	
	
}

void windowResized(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	TwWindowSize(windowWidth, windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);	

	g_LeftEyeImage->resize(windowWidth, windowHeight);
	g_RightEyeImage->resize(windowWidth, windowHeight);

}

void mouseEvt(int button,int state, int x,int y)
{
	if( !TwEventMouseButtonGLUT(button, state, x, y) )
	{
		if(button == GLUT_LEFT_BUTTON)
		{
			if(state == GLUT_DOWN)
				mouseActionState = 1;
			else
				mouseActionState = 0;
		}
		if(button == GLUT_RIGHT_BUTTON)
		{
			if(state == GLUT_DOWN)
				mouseActionState = 2;
			else
				mouseActionState = 0;
		}
	}
}

void mouseMotionEvt(int x, int y)
{
	if( !TwEventMouseMotionGLUT(x, y) )
	{
		if(lastMouseX == -1) lastMouseX = x;
		if(lastMouseY == -1) lastMouseY = y;

		float dx = (float) x - (float) lastMouseX;
		float dy = (float) y - (float) lastMouseY;

		if(mouseActionState == 1)
		{
			cameraAngle1 -= dx * 0.002;
			cameraAngle2 += dy * 0.002;
		}
		else if(mouseActionState == 2)
		{
			cameraDist += dy * 0.1;
			if(cameraDist < 0.01)
				cameraDist = 0.01;
		}

		lastMouseX = x;
		lastMouseY = y;
	}
}

void keyboardEvt(unsigned char key, int x, int y)
{
	if( !TwEventKeyboardGLUT(key, x, y) )
	{

	}
}

void specialKeyboardEvt(int key, int x, int y)
{
	if( !TwEventSpecialGLUT(key, x, y) )
	{

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
	glutCreateWindow("PBR viewer");

	initOpenGL();
	initGUI();
		
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouseEvt);
	glutMotionFunc(mouseMotionEvt);
	glutKeyboardFunc(keyboardEvt);
	glutReshapeFunc(windowResized);	
	glutPassiveMotionFunc(mouseMotionEvt);
	glutSpecialFunc(specialKeyboardEvt);

	glutMainLoop();

	gScene.clearScene();
	TwTerminate();

	return 0;
}