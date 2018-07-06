cmake_minimum_required(VERSION 2.8) 
project(OasisEngine C CXX) 

set(OASIS_APP_NAME OasisApp)

set(OASIS_SOURCE_FOLDER Source/Oasis)

add_definitions(-DOASIS_EXPORT=1)

# add sources 
set(SOURCES
    # Oasis 
    Source/Sample/Sample.cpp 

    Source/Sample/MeshRenderSystem.cpp 
    Source/Sample/MeshUtil.cpp 
    Source/Sample/MovementSystem.cpp 
    
    # Core  
    ${OASIS_SOURCE_FOLDER}/Core/Engine.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/EventManager.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/Display.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/Logger.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/TimerWindows.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/TimerLinux.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/TimeUtilWindows.cpp 
    ${OASIS_SOURCE_FOLDER}/Core/TimeUtilLinux.cpp 
    
    # Input 
    ${OASIS_SOURCE_FOLDER}/Input/Keyboard.cpp 

    # Graphics 
    ${OASIS_SOURCE_FOLDER}/Graphics/IndexBuffer.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/Mesh.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/Parameter.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/RenderTexture2D.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/Shader.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/Texture.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/Texture2D.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/VertexBuffer.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/VertexFormat.cpp 
    
    # Graphics/OpenGL 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLGraphicsDevice.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLIndexBuffer.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLRenderTexture2D.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLShader.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLTexture2D.cpp 
    ${OASIS_SOURCE_FOLDER}/Graphics/GL/GLVertexBuffer.cpp 
    
    # Math 
    ${OASIS_SOURCE_FOLDER}/Math/MathUtil.cpp 
    ${OASIS_SOURCE_FOLDER}/Math/Matrix4.cpp 
    ${OASIS_SOURCE_FOLDER}/Math/Quaternion.cpp 

    # Scene 
    ${OASIS_SOURCE_FOLDER}/Scene/Entity.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/EntityManager.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/Filter.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/FilterCache.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/Scene.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/SceneManager.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/System.cpp 
    ${OASIS_SOURCE_FOLDER}/Scene/SystemManager.cpp 
)

# add include directory 
include_directories(Include) 
include_directories(Source) 

# set up build type 
if(NOT CMAKE_BUILD_TYPE) 
    message(STATUS "Build type automatically set to DEBUG")
    set(CMAKE_BUILD_TYPE DEBUG)
else() 
    message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")
endif() 

set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -g -std=c++0x")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g -std=c++0x")

set(CMAKE_C_FLAGS_RELEASE     "${CMAKE_C_FLAGS_RELEASE} -Wall -O2 -std=c++0x")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2 -std=c++0x")

# check bit mode 
if(CMAKE_SIZEOF_VOID_P EQUAL 4) 
    message(STATUS "Building 32-bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8) 
    message(STATUS "Building 64-bit")
else() 
    math(EXPR BIT_COUNT "${CMAKE_SIZEOF_VOID_P} * 8")
    message(STATUS "Unknown bit mode: " ${BIT_COUNT})
endif() 

# add Find<Lib>.cmake files to path 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")

# find OpenGL
find_package(OpenGL REQUIRED)

# find SDL2 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}) 

# find GLEW 
find_package(GLEW REQUIRED) 
include_directories(${GLEW_INCLUDE_DIRS})

# build project 
add_executable(${OASIS_APP_NAME} ${SOURCES}) 
target_link_libraries(${OASIS_APP_NAME} 
    ${SDL2_LIBRARIES}
    ${GLEW_LIBRARIES} 
    ${OPENGL_LIBRARIES} 
)