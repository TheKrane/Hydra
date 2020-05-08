cmake_minimum_required(VERSION 3.10)
project(engine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules/")

find_package(SDL2_image)
if(SDL2_image_FOUND)
	find_package(SDL2)
endif()

if(SDL2_image_FOUND AND SDL2_FOUND)
elseif(WIN32)
	file(GLOB SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/win32/*.lib")
	
	set(ADDITIONAL_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/include")

else()
	add_subdirectory(thirdparty/sdl2/SDL2/ EXCLUDE_FROM_ALL)
	add_subdirectory(thirdparty/sdl2/SDL_image/ EXCLUDE_FROM_ALL)

	set(SDL2_IMAGE_LIBRARIES SDL2_image)
	
	add_library(SDL2::SDL2 ALIAS SDL2-static)
	set(ADDITIONAL_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/include")
endif()

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB sources
    "src/*.cpp"
)

add_library(engine STATIC ${sources})

target_include_directories(engine PUBLIC ${ADDITIONAL_INCLUDE_DIRECTORIES} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${BULLET_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm/include ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/objl/include)

if(WIN32)
	target_link_libraries(engine PUBLIC ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
else()
	target_link_libraries(engine PUBLIC SDL2::SDL2 PUBLIC ${SDL2_IMAGE_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
endif()
