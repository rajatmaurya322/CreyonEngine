#include "Shaderprogram.h"

namespace Creyon {

	Shaderprogram::Shaderprogram() {
		//Create a Shader program
		programId = glCreateProgram();
	}

	void Shaderprogram::addShader(const char* pathtoShader, GLenum Shadertype) {
		
		//Creates proper path to Shader Files
		Utility util = Utility::instance();
		std::filesystem::path abspath = util.CreyonSrcPath / pathtoShader ;

		//Read file's Shader source
		std::ifstream shaderfile;
		std::string shadercode;
		shaderfile.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			shaderfile.open(abspath);
			std::stringstream shaderstream;
			shaderstream << shaderfile.rdbuf();
			shaderfile.close();
			shadercode = shaderstream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "\nError! Can't Read Shader file Successfully";
		}

		//Convert shader code
		const char* shadersource = shadercode.c_str();

		//Create shader object
		unsigned int shaderID;
		shaderID = glCreateShader(Shadertype);   //Create shader of provided type
		glShaderSource(shaderID, 1, &shadersource, nullptr);  //Give shader object its source code
		
		//Compile Shader
		glCompileShader(shaderID);

		//Check errors
		int success;
		char infolog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		
		if (!success) {
			glGetShaderInfoLog(shaderID, 512, nullptr, infolog);  //Get shader log if errors are found
			std::cout << "\nERROR! Shader Compilation failed\n" << infolog << "\n";
		}
		else {  //Attach shader to program
			glAttachShader(programId, shaderID);
			glDeleteShader(shaderID);  //Delete shader as already attached to program object
		}
	}

	void Shaderprogram::link() {
		//Links the created shader program
		glLinkProgram(programId);

		//Check for errors in linking
		int success;
		char infolog[512];
		glGetProgramiv(programId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programId, 512, nullptr, infolog);
			std::cout << "\nError: Shader Program linking failed!\n" << infolog << "\n";
		}
	}

	GLint Shaderprogram::locateUniform(const std::string &uniformName) {
		return glGetUniformLocation(programId, uniformName.c_str());
	}

	void Shaderprogram::setInt(const std::string& uniformName, int value) {
		glUniform1i(locateUniform(uniformName), value);
	}

	void Shaderprogram::setFloat(const std::string& uniformName, float value) {
		glUniform1f(locateUniform(uniformName), value);
	}

	void Shaderprogram::setVec3(const std::string& uniformName, vector3d& value) {
		glUniform3f(locateUniform(uniformName), value.m_x, value.m_y, value.m_z);
	}

	void Shaderprogram::setColor(const std::string& uniformName, Color& value) {
		glUniform3f(locateUniform(uniformName), value.m_red, value.m_green, value.m_blue);
	}

	void Shaderprogram::setMat44(const std::string& uniformName, Mat44& value) {
		glUniformMatrix4fv(locateUniform(uniformName), 1, GL_TRUE, value.m_elems);
	}
}
