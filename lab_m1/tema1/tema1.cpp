#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema1::tema1()
{
}


tema1::~tema1()
{
}

void tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // Initialize angularStep
    angularStep = 0;

    // the green square
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 0.5f, 0), true);
    AddMeshToList(square1);

    // the background square
    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0.2f, 0.2f, 0.2f), false);
    AddMeshToList(square2);

    // the heart box
    Mesh* heart = object2D::CreateSquare("heartSquare", corner, squareSide, glm::vec3(0.8f, 0, 0), false);
    AddMeshToList(heart);

    // initialising the shooters
    for (int i = 0; i < 9; i++) {
        if (i < 3)
            shootersVec[i].row = 0;
        else if (i < 6)
            shootersVec[i].row = 1;
        else
            shootersVec[i].row = 2;
    }

    //heart
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(40, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),    //0
            VertexFormat(glm::vec3(80, 40, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(80, 60, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(60, 70, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(40, 50, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(20, 70, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(0, 60, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),    //6
            VertexFormat(glm::vec3(0, 40, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))     //7
        };

        vector<unsigned int> indices =
        {
            0, 4, 7,    // indices for first triangle
            7, 4, 6,
            6, 4, 5,
            0, 1, 4,
            4, 1, 2,
            4, 2, 3
        };

        meshes["heart"] = new Mesh("generated heart");
        meshes["heart"]->InitFromData(vertices, indices);
    }
    
    //color code: blue / yellow / orange / red
    //shooter1 - blue
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),     //0
            VertexFormat(glm::vec3(60, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),    //1
            VertexFormat(glm::vec3(50, 20, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(90, 40, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(90, 60, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(50, 80, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(30, 80, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(10, 60, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //7
            VertexFormat(glm::vec3(10, 20, 1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))    //8
        };

        vector<unsigned int> indices =
        {
            0, 1, 8,    // indices for first triangle
            1, 2, 8,
            8, 2, 7,
            7, 2, 6,
            6, 2, 5,
            5, 2, 4,
            4, 2, 3
        };

        meshes["shooter1"] = new Mesh("generated shooter");
        meshes["shooter1"]->InitFromData(vertices, indices);
    }

    //shooter2 - yellow
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),     //0
            VertexFormat(glm::vec3(60, 0, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),    //1
            VertexFormat(glm::vec3(50, 20, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(90, 40, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(90, 60, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(50, 80, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(30, 80, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(10, 60, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //7
            VertexFormat(glm::vec3(10, 20, 1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6))    //8
        };

        vector<unsigned int> indices =
        {
            0, 1, 8,    // indices for first triangle
            1, 2, 8,
            8, 2, 7,
            7, 2, 6,
            6, 2, 5,
            5, 2, 4,
            4, 2, 3
        };

        meshes["shooter2"] = new Mesh("generated shooter");
        meshes["shooter2"]->InitFromData(vertices, indices);
    }

    //shooter3 - orange
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),     //0
            VertexFormat(glm::vec3(60, 0, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),    //1
            VertexFormat(glm::vec3(50, 20, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(90, 40, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(90, 60, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(50, 80, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(30, 80, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(10, 60, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //7
            VertexFormat(glm::vec3(10, 20, 1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6))    //8
        };

        vector<unsigned int> indices =
        {
            0, 1, 8,    // indices for first triangle
            1, 2, 8,
            8, 2, 7,
            7, 2, 6,
            6, 2, 5,
            5, 2, 4,
            4, 2, 3
        };

        meshes["shooter3"] = new Mesh("generated shooter");
        meshes["shooter3"]->InitFromData(vertices, indices);
    }

    //shooter4 - red
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),     //0
            VertexFormat(glm::vec3(60, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),    //1
            VertexFormat(glm::vec3(50, 20, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(90, 40, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(90, 60, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(50, 80, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(30, 80, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(10, 60, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //7
            VertexFormat(glm::vec3(10, 20, 1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))    //8
        };

        vector<unsigned int> indices =
        {
            0, 1, 8,    // indices for first triangle
            1, 2, 8,
            8, 2, 7,
            7, 2, 6,
            6, 2, 5,
            5, 2, 4,
            4, 2, 3
        };

        meshes["shooter4"] = new Mesh("generated shooter");
        meshes["shooter4"]->InitFromData(vertices, indices);
    }
    
    //hexagon1 - gray
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(15, 25,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),     //0
            VertexFormat(glm::vec3(30, 0,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),      //1
            VertexFormat(glm::vec3(15, -25,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),    //2
            VertexFormat(glm::vec3(-15, -25,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(-30, 0,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),     //4
            VertexFormat(glm::vec3(-15, 25,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6))     //5
        };

        vector<unsigned int> indices =
        {
            0, 2, 1,    // indices for first triangle
            0, 3, 2,
            0, 5, 3,
            5, 4, 3
        };

        meshes["hexagon1"] = new Mesh("generated hexagon");
        meshes["hexagon1"]->InitFromData(vertices, indices);
    }

    //hexagon2 - blue
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(20, 35,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),  //0
            VertexFormat(glm::vec3(40, 0,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(20, -35,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-20, -35,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-40, 0,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(-20, 35,  1), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))  //5
        };

        vector<unsigned int> indices =
        {
            0, 2, 1,    // indices for first triangle
            0, 3, 2,
            0, 5, 3,
            5, 4, 3
        };

        meshes["hexagon2"] = new Mesh("generated hexagon");
        meshes["hexagon2"]->InitFromData(vertices, indices);
    }

    //hexagon3 - yellow
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(20, 35,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),  //0
            VertexFormat(glm::vec3(40, 0,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(20, -35,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-20, -35,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-40, 0,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(-20, 35,  1), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6))  //5
        };

        vector<unsigned int> indices =
        {
            0, 2, 1,    // indices for first triangle
            0, 3, 2,
            0, 5, 3,
            5, 4, 3
        };

        meshes["hexagon3"] = new Mesh("generated hexagon");
        meshes["hexagon3"]->InitFromData(vertices, indices);
    }

    //hexagon4 - orange
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(20, 35,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),  //0
            VertexFormat(glm::vec3(40, 0,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(20, -35,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-20, -35,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-40, 0,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(-20, 35,  1), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6))  //5
        };

        vector<unsigned int> indices =
        {
            0, 2, 1,    // indices for first triangle
            0, 3, 2,
            0, 5, 3,
            5, 4, 3
        };

        meshes["hexagon4"] = new Mesh("generated hexagon");
        meshes["hexagon4"]->InitFromData(vertices, indices);
    }

    //hexagon5 - red
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(20, 35,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),  //0
            VertexFormat(glm::vec3(40, 0,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(20, -35,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-20, -35,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-40, 0,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(-20, 35,  1), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))  //5
        };

        vector<unsigned int> indices =
        {
            0, 2, 1,    // indices for first triangle
            0, 3, 2,
            0, 5, 3,
            5, 4, 3
        };

        meshes["hexagon5"] = new Mesh("generated hexagon");
        meshes["hexagon5"]->InitFromData(vertices, indices);
    }

    //steauao - gray
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 18,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(18, 4,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(10, -15,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-10, -15,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-18, 4,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -6,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(7, -3,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-7, -3,  2), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star0"] = new Mesh("generated star");
        meshes["star0"]->InitFromData(vertices, indices);
    }

    //steaua1 - blue
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 22,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(23, 5,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(15, -20,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-15, -20,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-23, 5,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -10,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(9, -5,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-9, -5,  2), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star1"] = new Mesh("generated star");
        meshes["star1"]->InitFromData(vertices, indices);
    }

    //steaua2 - yellow
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 22,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(23, 5,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(15, -20,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-15, -20,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-23, 5,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -10,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(9, -5,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-9, -5,  2), glm::vec3(1, 1, 0), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star2"] = new Mesh("generated star");
        meshes["star2"]->InitFromData(vertices, indices);
    }

    //steaua3 - orange
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 22,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(23, 5,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(15, -20,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-15, -20,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-23, 5,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -10,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(9, -5,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-9, -5,  2), glm::vec3(1, 0.6f, 0), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star3"] = new Mesh("generated star");
        meshes["star3"]->InitFromData(vertices, indices);
    }

    //steaua4 - red
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 22,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(23, 5,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(15, -20,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-15, -20,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-23, 5,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -10,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(9, -5,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-9, -5,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star4"] = new Mesh("generated star");
        meshes["star4"]->InitFromData(vertices, indices);
    }

    //steaua5 - gold
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 22,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),   //0
            VertexFormat(glm::vec3(23, 5,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),   //1
            VertexFormat(glm::vec3(15, -20,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)), //2
            VertexFormat(glm::vec3(-15, -20,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),//3
            VertexFormat(glm::vec3(-23, 5,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),  //4
            VertexFormat(glm::vec3(0, -10,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),  //5
            VertexFormat(glm::vec3(9, -5,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6)),   //6
            VertexFormat(glm::vec3(-9, -5,  5), glm::vec3(1, 1, 0.6f), glm::vec3(0.2, 0.8, 0.6))   //7
        };

        vector<unsigned int> indices =
        {
            0, 3, 6,    // indices for first triangle
            0, 7, 2,
            1, 4, 5
        };

        meshes["star5"] = new Mesh("generated star");
        meshes["star5"]->InitFromData(vertices, indices);
    }

    // ending square
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  6), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),        //0
            VertexFormat(glm::vec3(1300, 0,  6), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),     //1
            VertexFormat(glm::vec3(1300, 750,  6), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(0, 750,  6), glm::vec3(0, 0, 0), glm::vec3(0.2, 0.8, 0.6))       //3
        };

        vector<unsigned int> indices =
        {
            0, 2, 3,    // indices for first triangle
            0, 1, 2
        };

        meshes["endsquare"] = new Mesh("generated end square");
        meshes["endsquare"]->InitFromData(vertices, indices);
    }

    endMatrix *= transform2D::Translate(0, 750);

    //lawnmower
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(20, 0,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),       //0
            VertexFormat(glm::vec3(60, 0,  2), glm::vec3(0.5f, 0, 0), glm::vec3(0.2, 0.8, 0.6)),    //1
            VertexFormat(glm::vec3(40, 20,  2), glm::vec3(0.5f, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //2
            VertexFormat(glm::vec3(60, 40,  2), glm::vec3(0.5f, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //3
            VertexFormat(glm::vec3(40, 60,  2), glm::vec3(0.5f, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //4
            VertexFormat(glm::vec3(60, 80,  2), glm::vec3(0.5f, 0, 0), glm::vec3(0.2, 0.8, 0.6)),   //5
            VertexFormat(glm::vec3(20, 80,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),      //6
            VertexFormat(glm::vec3(0, 60,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6)),       //7
            VertexFormat(glm::vec3(0, 20,  2), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))        //8
        };

        vector<unsigned int> indices =
        {
            0, 7, 8,    // indices for first triangle
            0, 6, 7,
            8, 5, 6,
            0, 3, 6,
            0, 1, 7
        };

        meshes["lawnmower"] = new Mesh("generated lawnmower");
        meshes["lawnmower"]->InitFromData(vertices, indices);
    }

    // initialising lawnmowers
    modelMatrix = glm::mat3(1) *= transform2D::Translate(10, 30);
    lawnmower newLawnmower(0, "lawnmower", modelMatrix);
    lawnmowers.push_back(newLawnmower);

    modelMatrix *= transform2D::Translate(0, 120);
    lawnmower newLawnmower2(1, "lawnmower", modelMatrix);
    lawnmowers.push_back(newLawnmower2);

    modelMatrix *= transform2D::Translate(0, 120);
    lawnmower newLawnmower3(2, "lawnmower", modelMatrix);
    lawnmowers.push_back(newLawnmower3);
}

void tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    glDeleteBuffers(1, &VAO);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.10f, 0.10f, 0.10f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema1::Update(float deltaTimeSeconds)
{
    int i, j;

    angularStep -= deltaTimeSeconds * 4;
    interval -= deltaTimeSeconds;
    intervalStars -= deltaTimeSeconds;

    for (i = 0; i < 9; i++)
        shootersVec[i].isShooting = false;

    // shooter death animation
    for (i = 0; i < 9; i++)
        if (shootersVec[i].isDed)
            if (shooterScales[i] < 0.3f)
                shootersVec[i].isPlanted = false;
            else
                shooterScales[i] -= deltaTimeSeconds * 3;
        else
            shooterScales[i] = 1;

    //geometria meniului(shooterele de cumparat, vietile si stelele)
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(100, 580);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(5, 8);
    RenderMesh2D(meshes["shooter1"], shaders["VertexColor"], modelMatrix);

    modelMatrix2 = modelMatrix * transform2D::Translate(45, -35);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);

    modelMatrix *= transform2D::Translate(122, -8);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(5, 8);
    RenderMesh2D(meshes["shooter2"], shaders["VertexColor"], modelMatrix);

    modelMatrix2 *= transform2D::Translate(105, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);
    modelMatrix2 *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);

    modelMatrix *= transform2D::Translate(122, -8);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(5, 8);
    RenderMesh2D(meshes["shooter3"], shaders["VertexColor"], modelMatrix);

    modelMatrix2 *= transform2D::Translate(88, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);
    modelMatrix2 *= transform2D::Translate(40, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);

    modelMatrix *= transform2D::Translate(122, -8);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(5, 8);
    RenderMesh2D(meshes["shooter4"], shaders["VertexColor"], modelMatrix);

    modelMatrix2 *= transform2D::Translate(76, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);
    modelMatrix2 *= transform2D::Translate(32, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);
    modelMatrix2 *= transform2D::Translate(32, 0);
    RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);

    // geometria balantei jucatorului
    modelMatrix2 *= transform2D::Translate(264, 0);
    for (i = 0; i < numStars; i++) {
        RenderMesh2D(meshes["star0"], shaders["VertexColor"], modelMatrix2);
        modelMatrix2 *= transform2D::Translate(40, 0);
    }

    modelMatrix *= transform2D::Translate(320, -8);
    RenderMesh2D(meshes["heartSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(10, 12);
    if (healthPoints > 0)
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(120, -12);
    RenderMesh2D(meshes["heartSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(10, 12);
    if (healthPoints > 1)
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(120, -12);
    if (healthPoints > 1)
        RenderMesh2D(meshes["heartSquare"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(10, 12);
    if (healthPoints > 2)
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);

    //geometria scenei(patratele, lawnmowerele si lansatoarele):
    modelMatrix = glm::mat3(1); // pt lawn squares
    modelMatrix *= transform2D::Translate(80, 20);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[0].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[0]); // pt lansator 1
        RenderMesh2D(meshes[shootersVec[0].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[0].posX = modelMatrix[2][0];
    shootersVec[0].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[1].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[1]); // pt lansator 2
        RenderMesh2D(meshes[shootersVec[1].type], shaders["VertexColor"], modelMatrix2);

    }
    shootersVec[1].posX = modelMatrix[2][0];
    shootersVec[1].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[2].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[2]); // pt lansator 3
        RenderMesh2D(meshes[shootersVec[2].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[2].posX = modelMatrix[2][0];
    shootersVec[2].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(0, 120);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[3].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[3]); // pt lansator 4
        RenderMesh2D(meshes[shootersVec[3].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[3].posX = modelMatrix[2][0];
    shootersVec[3].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(-120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[4].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[4]); // pt lansator 5
        RenderMesh2D(meshes[shootersVec[4].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[4].posX = modelMatrix[2][0];
    shootersVec[4].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(-120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[5].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[5]); // pt lansator 6
        RenderMesh2D(meshes[shootersVec[5].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[5].posX = modelMatrix[2][0];
    shootersVec[5].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(0, 120);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[6].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[6]); // pt lansator 7
        RenderMesh2D(meshes[shootersVec[6].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[6].posX = modelMatrix[2][0];
    shootersVec[6].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[7].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[7]); // pt lansator 8
        RenderMesh2D(meshes[shootersVec[7].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[7].posX = modelMatrix[2][0];
    shootersVec[7].modelMatrix = modelMatrix;

    modelMatrix *= transform2D::Translate(120, 0);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    if (shootersVec[8].isPlanted) {
        modelMatrix2 = modelMatrix * transform2D::Scale(1, shooterScales[8]); // pt lansator 9
        RenderMesh2D(meshes[shootersVec[8].type], shaders["VertexColor"], modelMatrix2);
    }
    shootersVec[8].posX = modelMatrix[2][0];
    shootersVec[8].modelMatrix = modelMatrix;

    for (i = 0; i < lawnmowers.size(); i++)
        RenderMesh2D(meshes[lawnmowers[i].mesh], shaders["VertexColor"], lawnmowers[i].modelMatrix);

    // randam cate un nou zombie cand intervalul se termina
    if (interval <= 0) {
        int row = rand() % 3;
        tip = rand() % 4;
        zombie newZombie(3, row, tip, tipuriZombie[tip], glm::mat3(1) * transform2D::Translate(1300, 70 + row * 120));
        zombies.push_back(newZombie);
        interval = (rand() % (10 - 1)) + 2;
        //cout << "Intervalul e " << interval << "\n";
    }

    // randam zombii
    if (tip >= 0) { // daca am creat macar un index in vector - incearca fara
        for (i = 0; i < zombies.size(); i++) {
            if (zombies[i].health > 0) // daca traiesc se misca
                zombies[i].modelMatrix *= transform2D::Translate(-deltaTimeSeconds * 100, 0);
            else // death animation
                zombies[i].modelMatrix *= transform2D::Scale(zombies[i].scale, zombies[i].scale);
            RenderMesh2D(meshes["hexagon1"], shaders["VertexColor"], zombies[i].modelMatrix);
            RenderMesh2D(meshes[zombies[i].type], shaders["VertexColor"], zombies[i].modelMatrix);
        }
    }

    // shooters identify the zombies and the zombies eat the shooters
    for (i = 0; i < 9; i++) {
        if (!shootersVec[i].isDed)
            for (j = 0; j < zombies.size(); j++)
                if (zombies[j].row == shootersVec[i].row && zombies[j].health > 0) {
                    if (zombies[j].tip == shootersVec[i].tip)
                        if (shootersVec[i].posX <= zombies[j].modelMatrix[2][0] - 130) { // the shooter has seen the zombie and starts shooting it
                            shootersVec[i].isShooting = true;
                        }
                    if (shootersVec[i].posX >= zombies[j].modelMatrix[2][0] - 130 && shootersVec[i].posX - 30 <= zombies[j].modelMatrix[2][0]) // the zombie eats the shooter
                        shootersVec[i].isDed = true;
                }
    }

    // shooters shoot the projectiles
    for (i = 0; i < 9; i++) {
        if (!shootersVec[i].isDed && shootersVec[i].isShooting) {
            //cream proiectilele
            if (shootersVec[i].shotInterval <= 0) {

                projectile newProjectile(shootersVec[i].row, shootersVec[i].tip, tipuriStars[shootersVec[i].tip], shootersVec[i].modelMatrix[2][0] + 50, shootersVec[i].modelMatrix[2][1] + 50);
                projectiles.push_back(newProjectile);

                shootersVec[i].shotInterval = 2;
            }
            shootersVec[i].shotInterval -= deltaTimeSeconds;
        }
    }

    // rendering the projectiles
    for (i = 0; i < projectiles.size(); i++) {
        projectiles[i].modelMatrix = glm::mat3(1);
        projectiles[i].modelMatrix *= transform2D::Translate(projectiles[i].posX, projectiles[i].posY);
        projectiles[i].modelMatrix *= transform2D::Rotate(angularStep);

        RenderMesh2D(meshes[projectiles[i].type], shaders["VertexColor"], projectiles[i].modelMatrix);

        projectiles[i].posX += deltaTimeSeconds * 400;
    }

    // zombie death animation
    for (i = 0; i < zombies.size(); i++)
        if (zombies[i].health < 1)
            if (zombies[i].scale <= 0.7f)
                zombies.erase(zombies.begin() + i);
            else
                zombies[i].scale -= deltaTimeSeconds;

    // zombies take damage from the projectiles
    for (i = 0; i < zombies.size(); i++) {
        for (j = 0; j < projectiles.size(); j++)
            if (zombies[i].health > 0 && projectiles[j].row == zombies[i].row && projectiles[j].tip == zombies[i].tip && zombies[i].modelMatrix[2][0] <= projectiles[j].modelMatrix[2][0] + 40) {
                zombies[i].health -= 1;
                projectiles.erase(projectiles.begin() + j);
            }
        if (zombies[i].modelMatrix[2][0] <= 0 && zombies[i].health > 0) { // daca un zombie trece de prag pierdem o viata
            healthPoints -= 1;
            zombies[i].health = 0;
        }
    }

    // lawnmowers start if a zombie is nearby
    for (i = 0; i < lawnmowers.size(); i++)
        for (j = 0; j < zombies.size(); j++)
            if (lawnmowers[i].row == zombies[j].row && lawnmowers[i].modelMatrix[2][0] > zombies[j].modelMatrix[2][0] - 100)
                lawnmowers[i].hasStarted = true;

    // lawnmowers move and off zombies
    for (i = 0; i < lawnmowers.size(); i++) {
        if (lawnmowers[i].hasStarted) {
            for (j = 0; j < zombies.size(); j++)
                if (lawnmowers[i].row == zombies[j].row && lawnmowers[i].modelMatrix[2][0] > zombies[j].modelMatrix[2][0] - 100)
                    zombies[j].health = 0;
            lawnmowers[i].modelMatrix *= transform2D::Translate(deltaTimeSeconds * 250, 0);
        }
        if (lawnmowers[i].modelMatrix[2][0] > 1350)
            lawnmowers.erase(lawnmowers.begin() + i);
    }

    // randam shooterul pt drag and drop
    if (dragSwitch == 1)
        RenderMesh2D(meshes[selectedShooter.type], shaders["VertexColor"], selectedShooter.modelMatrix);

    // calculam pozitia stelutelor si le adaugam in vectorul de stele
    if (intervalStars <= 0) {
        stars.clear(); //golim vectorul de stelele care nu au fost colectate

        for (i = 0; i <= rand() % 3; i++) {
            int sX = (rand() % (1100 - 200)) + 200, sY = (rand() % (600 - 50)) + 50;
            //cout << "Starx = " << sX << " si Stary = " << sY << "\n";
            star newStar(sX, sY, glm::mat3(1) * transform2D::Translate(sX, sY));
            stars.push_back(newStar);
        }
        intervalStars = 5;
    }

    // randam stelele
    for (i = 0; i < stars.size(); i++) {
        RenderMesh2D(meshes["star5"], shaders["VertexColor"], stars[i].modelMatrix);
        stars[i].modelMatrix *= transform2D::Rotate(-deltaTimeSeconds);
    }

    //ending animation
    if (healthPoints < 1) {
        if (endMatrix[2][1] > 0)
            endMatrix *= transform2D::Translate(0, - deltaTimeSeconds * 300);
        RenderMesh2D(meshes["endsquare"], shaders["VertexColor"], endMatrix);
    }

}


void tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{    
    // Pentru drag-and-drop
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        //cout << "Cursor moved at " << mouseX << ", " << mouseY << "\n";
        selectedShooter.modelMatrix = glm::mat3(1) * transform2D::Translate(mouseX - 40, 670 - mouseY);
    }
}


void tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    int col = -1, row = -1, i;
    int selectedShooterId = -1;
    
    // Pentru stergerea lansatoarelor
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        //cout << "Cursor r-clicked at " << mouseX << ", " << mouseY << "\n";
        if (mouseX >= 80 && mouseX <= 180) {
            //cout << "Selectat pt stergere coloana 1\n";
            col = 0;
        }
        if (mouseX >= 200 && mouseX <= 300) {
            //cout << "Selectat pt stergere coloana 2\n";
            col = 1;
        }
        if (mouseX >= 320 && mouseX <= 420) {
            //cout << "Selectat pt stergere coloana 3\n";
            col = 2;
        }
        if (mouseY >= 600 && mouseY <= 700) {
            //cout << "Selectat pt stergere randul 1\n";
            row = 0;
        }
        if (mouseY >= 480 && mouseY <= 580) {
            //cout << "Selectat pt stergere randul 2\n";
            row = 1;
        }
        if (mouseY >= 360 && mouseY <= 460) {
            //cout << "Selectat pt stergere randul 3\n";
            row = 2;
        }

        if (col >= 0 && row >= 0) {
            if (row == 0 || row == 2)
                shootersVec[row * 3 + col].isDed = true;
            else
                shootersVec[3 + (2 - col)].isDed = true;
        }

        mouseSwitch = 0;
    }

    // pentru colectarea stelelor si disparitia lor din scena
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        for (i = 0; i < stars.size(); i++)
            if (abs(stars[i].modelMatrix[2][0] - mouseX) <= 25 && abs((720 - stars[i].modelMatrix[2][1]) - mouseY) <= 25) {
                if (numStars < 9)
                    numStars++;
                stars.erase(stars.begin() + i);
            }
    }

    col = -1; row = -1;
    // pentru plantarea lansatoarelor
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && mouseSwitch == 1) {
        if (mouseX >= 80 && mouseX <= 180) {
            //cout << "Selectat pt plantare coloana 1\n";
            col = 0;
        }
        if (mouseX >= 200 && mouseX <= 300) {
            //cout << "Selectat pt plantare coloana 2\n";
            col = 1;
        }
        if (mouseX >= 320 && mouseX <= 420) {
            //cout << "Selectat pt plantare coloana 3\n";
            col = 2;
        }
        if (mouseY >= 600 && mouseY <= 700) {
            //cout << "Selectat pt plantare randul 1\n";
            row = 0;
        }
        if (mouseY >= 480 && mouseY <= 580) {
            //cout << "Selectat pt plantare randul 2\n";
            row = 1;
        }
        if (mouseY >= 360 && mouseY <= 460) {
            //cout << "Selectat pt plantare randul 3\n";
            row = 2;
        }
        // plantarea propriu-zisa
        if (col >= 0 && row >= 0 && numStars >= selectedShooter.cost) {
            if (!shootersVec[row * 3 + col].isPlanted && (row == 0 || row == 2)) {
                shootersVec[row * 3 + col].isPlanted = true;
                shootersVec[row * 3 + col].isDed = false;
                shootersVec[row * 3 + col].tip = selectedShooter.tip;
                shootersVec[row * 3 + col].type = selectedShooter.type;
                numStars -= selectedShooter.cost;
            }
            if (!shootersVec[3 + (2 - col)].isPlanted && row == 1) {
                shootersVec[3 + (2 - col)].isPlanted = true;
                shootersVec[3 + (2 - col)].isDed = false;
                shootersVec[3 + (2 - col)].tip = selectedShooter.tip;
                shootersVec[3 + (2 - col)].type = selectedShooter.type;
                numStars -= selectedShooter.cost;
            }
        }
        mouseSwitch = 0;
        dragSwitch = 0;
    }

    // selectarea lansatoarelor
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        if (mouseY >= 40 && mouseY <= 140) {
            if (mouseX >= 100 && mouseX <= 200) {
                //cout << "S-a selectat shooterul 1\n";
                selectedShooterId = 0;
                selectedShooter.cost = 1;
                selectedShooter.tip = 0;
                selectedShooter.type = tipuriShooter[0];
                selectedShooter.modelMatrix = glm::mat3(1) * transform2D::Translate(mouseX - 40, 670 - mouseY);
                mouseSwitch = 1;
                dragSwitch = 1;
            }
            else if (mouseX >= 227 && mouseX <= 327) {
                //cout << "S-a selectat shooterul 2\n";
                selectedShooterId = 1;
                selectedShooter.cost = 2;
                selectedShooter.tip = 1;
                selectedShooter.type = tipuriShooter[1];
                selectedShooter.modelMatrix = glm::mat3(1) * transform2D::Translate(mouseX - 40, 670 - mouseY);
                mouseSwitch = 1;
                dragSwitch = 1;
            }
            else if (mouseX >= 354 && mouseX <= 454) {
                //cout << "S-a selectat shooterul 3\n";
                selectedShooterId = 2;
                selectedShooter.cost = 2;
                selectedShooter.tip = 2;
                selectedShooter.type = tipuriShooter[2];
                selectedShooter.modelMatrix = glm::mat3(1) * transform2D::Translate(mouseX - 40, 670 - mouseY);
                mouseSwitch = 1;
                dragSwitch = 1;
            }
            else if (mouseX >= 480 && mouseX <= 580) {
                //cout << "S-a selectat shooterul 4\n";
                selectedShooterId = 3;
                selectedShooter.cost = 3;
                selectedShooter.tip = 3;
                selectedShooter.type = tipuriShooter[3];
                selectedShooter.modelMatrix = glm::mat3(1) * transform2D::Translate(mouseX - 40, 670 - mouseY);
                mouseSwitch = 1;
                dragSwitch = 1;
            }
            else {
                mouseSwitch = 0;
                dragSwitch = 0;
            }
        }
        else {
            mouseSwitch = 0;
            dragSwitch = 0;
        }
    }

}


void tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    int col = -1, row = -1;

    //pentru plantarea lansatoarelor dupa drag-and-drop
    if (mouseX >= 80 && mouseX <= 180) {
        //cout << "Selectat pt plantare coloana 1\n";
        col = 0;
    }
    if (mouseX >= 200 && mouseX <= 300) {
        //cout << "Selectat pt plantare coloana 2\n";
        col = 1;
    }
    if (mouseX >= 320 && mouseX <= 420) {
        //cout << "Selectat pt plantare coloana 3\n";
        col = 2;
    }
    if (mouseY >= 600 && mouseY <= 700) {
        //cout << "Selectat pt plantare randul 1\n";
        row = 0;
    }
    if (mouseY >= 480 && mouseY <= 580) {
        //cout << "Selectat pt plantare randul 2\n";
        row = 1;
    }
    if (mouseY >= 360 && mouseY <= 460) {
        //cout << "Selectat pt plantare randul 3\n";
        row = 2;
    }
    // plantarea propriu-zisa
    if (col >= 0 && row >= 0 && numStars >= selectedShooter.cost && dragSwitch == 1) {
        if (!shootersVec[row * 3 + col].isPlanted && (row == 0 || row == 2)) {
            shootersVec[row * 3 + col].isPlanted = true;
            shootersVec[row * 3 + col].isDed = false;
            shootersVec[row * 3 + col].tip = selectedShooter.tip;
            shootersVec[row * 3 + col].type = selectedShooter.type;
            numStars -= selectedShooter.cost;
            mouseSwitch = 0;
        }
        if (!shootersVec[3 + (2 - col)].isPlanted && row == 1) {
            shootersVec[3 + (2 - col)].isPlanted = true;
            shootersVec[3 + (2 - col)].isDed = false;
            shootersVec[3 + (2 - col)].tip = selectedShooter.tip;
            shootersVec[3 + (2 - col)].type = selectedShooter.type;
            numStars -= selectedShooter.cost;
            mouseSwitch = 0;
        }
    }

    dragSwitch = 0;
}


void tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema1::OnWindowResize(int width, int height)
{
}
