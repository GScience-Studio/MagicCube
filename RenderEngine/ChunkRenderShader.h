#pragma once

#include "GLManager.h"

//glm
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

extern render_program* chunkRenderProgram;

class chunk_render_program :public render_program
{
private:
	gl_manager& glInstance = gl_manager::getInstance();

	//light location
	GLuint _lightPosLocation;

	//light lock
	std::mutex lightLock;

	//eyes location
	GLuint _eyesPosLocation;

	//is in player sight?
	bool isInSight = false;

	//last golbal camera
	camera lastGlobalCamera;

	//frustum planes
	float g_frustumPlanes[6][4];

	float lightVec[3]{ 0.0,0.0,0.0 };

	void calculateFrustumPlanes(glm::mat4& modleVerMatrix)
	{
		const float* p;   // projection matrix
		const float* mv;  // model-view matrix
		float mvp[16]; // model-view-projection matrix
		float t;

		p = glm::value_ptr(gl_manager::getInstance().getPerspective());
		mv = glm::value_ptr(modleVerMatrix);

		//
		// Concatenate the projection matrix and the model-view matrix to produce
		// a combined model-view-projection matrix.
		//

		mvp[0] = mv[0] * p[0] + mv[1] * p[4] + mv[2] * p[8] + mv[3] * p[12];
		mvp[1] = mv[0] * p[1] + mv[1] * p[5] + mv[2] * p[9] + mv[3] * p[13];
		mvp[2] = mv[0] * p[2] + mv[1] * p[6] + mv[2] * p[10] + mv[3] * p[14];
		mvp[3] = mv[0] * p[3] + mv[1] * p[7] + mv[2] * p[11] + mv[3] * p[15];

		mvp[4] = mv[4] * p[0] + mv[5] * p[4] + mv[6] * p[8] + mv[7] * p[12];
		mvp[5] = mv[4] * p[1] + mv[5] * p[5] + mv[6] * p[9] + mv[7] * p[13];
		mvp[6] = mv[4] * p[2] + mv[5] * p[6] + mv[6] * p[10] + mv[7] * p[14];
		mvp[7] = mv[4] * p[3] + mv[5] * p[7] + mv[6] * p[11] + mv[7] * p[15];

		mvp[8] = mv[8] * p[0] + mv[9] * p[4] + mv[10] * p[8] + mv[11] * p[12];
		mvp[9] = mv[8] * p[1] + mv[9] * p[5] + mv[10] * p[9] + mv[11] * p[13];
		mvp[10] = mv[8] * p[2] + mv[9] * p[6] + mv[10] * p[10] + mv[11] * p[14];
		mvp[11] = mv[8] * p[3] + mv[9] * p[7] + mv[10] * p[11] + mv[11] * p[15];

		mvp[12] = mv[12] * p[0] + mv[13] * p[4] + mv[14] * p[8] + mv[15] * p[12];
		mvp[13] = mv[12] * p[1] + mv[13] * p[5] + mv[14] * p[9] + mv[15] * p[13];
		mvp[14] = mv[12] * p[2] + mv[13] * p[6] + mv[14] * p[10] + mv[15] * p[14];
		mvp[15] = mv[12] * p[3] + mv[13] * p[7] + mv[14] * p[11] + mv[15] * p[15];

		//
		// Extract the frustum's right clipping plane and normalize it.
		//

		g_frustumPlanes[0][0] = mvp[3] - mvp[0];
		g_frustumPlanes[0][1] = mvp[7] - mvp[4];
		g_frustumPlanes[0][2] = mvp[11] - mvp[8];
		g_frustumPlanes[0][3] = mvp[15] - mvp[12];

		t = (float)sqrt(g_frustumPlanes[0][0] * g_frustumPlanes[0][0] +
			g_frustumPlanes[0][1] * g_frustumPlanes[0][1] +
			g_frustumPlanes[0][2] * g_frustumPlanes[0][2]);

		g_frustumPlanes[0][0] /= t;
		g_frustumPlanes[0][1] /= t;
		g_frustumPlanes[0][2] /= t;
		g_frustumPlanes[0][3] /= t;

		//
		// Extract the frustum's left clipping plane and normalize it.
		//

		g_frustumPlanes[1][0] = mvp[3] + mvp[0];
		g_frustumPlanes[1][1] = mvp[7] + mvp[4];
		g_frustumPlanes[1][2] = mvp[11] + mvp[8];
		g_frustumPlanes[1][3] = mvp[15] + mvp[12];

		t = (float)sqrt(g_frustumPlanes[1][0] * g_frustumPlanes[1][0] +
			g_frustumPlanes[1][1] * g_frustumPlanes[1][1] +
			g_frustumPlanes[1][2] * g_frustumPlanes[1][2]);

		g_frustumPlanes[1][0] /= t;
		g_frustumPlanes[1][1] /= t;
		g_frustumPlanes[1][2] /= t;
		g_frustumPlanes[1][3] /= t;



		//
		// Extract the frustum's bottom clipping plane and normalize it.
		//

		g_frustumPlanes[2][0] = mvp[3] + mvp[1];
		g_frustumPlanes[2][1] = mvp[7] + mvp[5];
		g_frustumPlanes[2][2] = mvp[11] + mvp[9];
		g_frustumPlanes[2][3] = mvp[15] + mvp[13];

		t = (float)sqrt(g_frustumPlanes[2][0] * g_frustumPlanes[2][0] +
			g_frustumPlanes[2][1] * g_frustumPlanes[2][1] +
			g_frustumPlanes[2][2] * g_frustumPlanes[2][2]);

		g_frustumPlanes[2][0] /= t;
		g_frustumPlanes[2][1] /= t;
		g_frustumPlanes[2][2] /= t;
		g_frustumPlanes[2][3] /= t;

		//
		// Extract the frustum's top clipping plane and normalize it.
		//

		g_frustumPlanes[3][0] = mvp[3] - mvp[1];
		g_frustumPlanes[3][1] = mvp[7] - mvp[5];
		g_frustumPlanes[3][2] = mvp[11] - mvp[9];
		g_frustumPlanes[3][3] = mvp[15] - mvp[13];

		t = (float)sqrt(g_frustumPlanes[3][0] * g_frustumPlanes[3][0] +
			g_frustumPlanes[3][1] * g_frustumPlanes[3][1] +
			g_frustumPlanes[3][2] * g_frustumPlanes[3][2]);

		g_frustumPlanes[3][0] /= t;
		g_frustumPlanes[3][1] /= t;
		g_frustumPlanes[3][2] /= t;
		g_frustumPlanes[3][3] /= t;



		//
		// Extract the frustum's far clipping plane and normalize it.
		//

		g_frustumPlanes[4][0] = mvp[3] - mvp[2];
		g_frustumPlanes[4][1] = mvp[7] - mvp[6];
		g_frustumPlanes[4][2] = mvp[11] - mvp[10];
		g_frustumPlanes[4][3] = mvp[15] - mvp[14];

		t = (float)sqrt(g_frustumPlanes[4][0] * g_frustumPlanes[4][0] +
			g_frustumPlanes[4][1] * g_frustumPlanes[4][1] +
			g_frustumPlanes[4][2] * g_frustumPlanes[4][2]);

		g_frustumPlanes[4][0] /= t;
		g_frustumPlanes[4][1] /= t;
		g_frustumPlanes[4][2] /= t;
		g_frustumPlanes[4][3] /= t;

		//
		// Extract the frustum's near clipping plane and normalize it.
		//

		g_frustumPlanes[5][0] = mvp[3] + mvp[2];
		g_frustumPlanes[5][1] = mvp[7] + mvp[6];
		g_frustumPlanes[5][2] = mvp[11] + mvp[10];
		g_frustumPlanes[5][3] = mvp[15] + mvp[14];

		t = (float)sqrt(g_frustumPlanes[5][0] * g_frustumPlanes[5][0] +
			g_frustumPlanes[5][1] * g_frustumPlanes[5][1] +
			g_frustumPlanes[5][2] * g_frustumPlanes[5][2]);

		g_frustumPlanes[5][0] /= t;
		g_frustumPlanes[5][1] /= t;
		g_frustumPlanes[5][2] /= t;
		g_frustumPlanes[5][3] /= t;
	}

	bool isCubeInFrustum(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((g_frustumPlanes[i][0] * x1 + g_frustumPlanes[i][1] * y1 + g_frustumPlanes[i][2] * z1 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x2 + g_frustumPlanes[i][1] * y1 + g_frustumPlanes[i][2] * z1 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x1 + g_frustumPlanes[i][1] * y2 + g_frustumPlanes[i][2] * z1 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x2 + g_frustumPlanes[i][1] * y2 + g_frustumPlanes[i][2] * z1 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x1 + g_frustumPlanes[i][1] * y1 + g_frustumPlanes[i][2] * z2 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x2 + g_frustumPlanes[i][1] * y1 + g_frustumPlanes[i][2] * z2 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x1 + g_frustumPlanes[i][1] * y2 + g_frustumPlanes[i][2] * z2 + g_frustumPlanes[i][3] <= 0.0F) &&
				(g_frustumPlanes[i][0] * x2 + g_frustumPlanes[i][1] * y2 + g_frustumPlanes[i][2] * z2 + g_frustumPlanes[i][3] <= 0.0F))
			{
				return false;
			}
		}
		return true;
	}

	void _setCamera(camera& globalCamera, camera& modelLocation)
	{
		gl_manager::getInstance().useShaderProgram(_programID);

		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(modelLocation.getLocation()->getX() -globalCamera.getLocation()->getX(), modelLocation.getLocation()->getY() -globalCamera.getLocation()->getY(), modelLocation.getLocation()->getZ() -globalCamera.getLocation()->getZ()));
		glm::mat4 cameraRotate = glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 modleCamera = cameraRotate * cameraTranslate;

		calculateFrustumPlanes(modleCamera);

		isInSight = isCubeInFrustum(0.0, 0.0, 0.0, 16.0, 16.0, 16.0);

		if (!isInSight)
			return;

		glm::mat4 projection = gl_manager::getInstance().getPerspective() * modleCamera;

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(projection));
	}

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera& globalCamera, camera& modelLocation)
	{
		_setCamera(globalCamera, modelLocation);

		//check whether the chunk is in player's sight
		
		//set light(can't use now)
		/*
		if (lightLock.try_lock())
		{
			glUniform3fv(_lightPosLocation, 1, lightVec);

			lightLock.unlock();
		}
		*/

		if (isInSight)
		{
			glInstance.useBuffer(buffer);
			glInstance.useShaderProgram(_programID);

			glDrawArrays(GL_POINTS, first, count);
		}
	}

	//init
	void _init()
	{
		//set texture
		glUniform1i(glGetUniformLocation(_programID, "texture"), 0);
		glUniform1i(glGetUniformLocation(_programID, "normal"), 1);
		glUniform1i(glGetUniformLocation(_programID, "depthMap"), 2);

		//get light location
		_lightPosLocation = glGetUniformLocation(_programID, "lightPos");
		_eyesPosLocation = glGetUniformLocation(_programID, "eyesPos");
	}
	//create buffer by daat
	void _setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const;

public:
	/*set light pos
	from the input location to 0,0,0
	*/
	void setLight(float x, float y, float z)
	{
		lightLock.lock();

		lightVec[0] = x;
		lightVec[1] = y;
		lightVec[2] = z;

		lightLock.unlock();
	}
};