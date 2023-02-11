#pragma once

//All includes and aliases for Creyon engine are stored here

#include "MathEngine/matrix2x2.h"
#include "MathEngine/matrix3x3.h"
#include "MathEngine/matrix4x4.h"
#include "MathEngine/vector4d.h"
#include "MathEngine/vector3d.h"
#include "MathEngine/vector2d.h"
#include "MathEngine/transforms.h"
#include "MathEngine/quaternion.h"
#include "Utilities/Utility.h"
#include "Render/CreyonWindow.h"
#include "Render/Camera.h"
#include "Render/Shaderprogram.h"
#include "Render/stb_image.h"
#include "Render/Texture.h"
#include "Render/VertexBuffer.h"
#include "Render/VertexArray.h"
#include "Render/Color.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

using std::cout;
using std::cin;
using Creyon::CreyonWindow;
using Creyon::vector3d;
using Creyon::vector4d;
using Creyon::Shaderprogram;