#ifndef NATIVESHAPES
#define NATIVESHAPES


namespace NativeShapes {

	namespace Cube {
        const float vertices[64] = {
            
        };

        const int indices[36] = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            7, 3, 0,
            7, 0, 4,

            6, 2, 1,
            6, 1, 5,

            4, 5, 1,
            4, 1, 0,

            7, 6, 2,
            7, 2, 3
        };

        const size_t verticesSize = sizeof(vertices);
        const size_t indicesSize = sizeof(indices);
	};

	namespace FlatPlane {
        const float vertices[32] = 
        {
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
        };

        const int indices[6] = {
            0, 1, 2,
            1, 2, 3
        };
        
        const size_t verticesSize = sizeof(vertices);
        const size_t indicesSize = sizeof(indices);
	};
};

#endif