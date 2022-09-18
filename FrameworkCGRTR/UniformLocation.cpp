#include "UniformLocation.h"

template<> void UniformLocation<float>::Bind()
{
	int floatLocation = glGetUniformLocation(spID, unifLocName.c_str());
	glUniform1f(floatLocation, *unifLocData);
};
template<> void UniformLocation<glm::vec4>::Bind()
{
	int vec4Location = glGetUniformLocation(spID, unifLocName.c_str());
	glUniform4fv(vec4Location, 1, glm::value_ptr(*unifLocData));
};
template<> void UniformLocation<glm::mat4>::Bind()
{
	int mat4Location = glGetUniformLocation(spID, unifLocName.c_str());
	glUniformMatrix4fv(mat4Location, 1, GL_FALSE, glm::value_ptr(*unifLocData));
};