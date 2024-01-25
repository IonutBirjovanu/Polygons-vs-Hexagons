#pragma once

#include "components/simple_scene.h"
#include <string>


namespace m1
{
    struct shooter //vector de shooters
    {
        std::string type;
        int cost, column, row, tip;
        bool isPlanted = false, isShooting = false, isDed = true;
        float posX, shotInterval = 1;
        glm::mat3 modelMatrix;

        //shooter();

    };

    struct zombie //vector de zombies
    {
        int health, row, tip;
        std::string type;
        glm::mat3 modelMatrix;
        float scale = 1;

        //zombie() {};

        zombie(int initHealth, int initRow, int initTip, std::string initType, glm::mat3 initModelMatrix) {
            health = initHealth;
            row = initRow;
            tip = initTip;
            type = initType;
            modelMatrix = initModelMatrix;
        };
    };

    struct projectile //vector de projectiles
    {
        int row, tip, posX, posY;
        std::string type;
        glm::mat3 modelMatrix;

        projectile(int initRow, int initTip, std::string initType, int initPosX, int initPosY) {
            row = initRow;
            tip = initTip;
            type = initType;
            posX = initPosX;
            posY = initPosY;
        };
    };

    struct lawnmower
    {
        int row;
        std::string mesh;
        glm::mat3 modelMatrix;
        bool hasStarted = false;

        lawnmower(int initRow, std::string initMesh, glm::mat3 initModelMatrix) {
            row = initRow;
            mesh = initMesh;
            modelMatrix = initModelMatrix;
        }
    };

    struct star
    {
        float starX, starY;
        glm::mat3 modelMatrix;

        star(float initStarX, float initStarY, glm::mat3 initModelMatrix) {
            starX = initStarX;
            starY = initStarY;
            modelMatrix = initModelMatrix;
        }
    };
    
    class tema1 : public gfxc::SimpleScene
    {
    public:
        tema1();
        ~tema1();

        void Init() override;

    private:
        void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix, modelMatrix2, endMatrix = glm::mat3(1);
        float angularStep;
        int tip = -1, healthPoints = 3, numStars = 5, mouseSwitch = 0, dragSwitch = 0;
        shooter shootersVec[9] = {}, selectedShooter;
        float interval = 5, intervalStars = 5;
        std::vector<zombie> zombies;
        std::string tipuriZombie[4] = { "hexagon2", "hexagon3", "hexagon4", "hexagon5" };
        std::string tipuriShooter[4] = { "shooter1", "shooter2", "shooter3", "shooter4" };
        std::string tipuriStars[4] = { "star1", "star2", "star3", "star4" };
        std::vector<projectile> projectiles;
        std::vector<lawnmower> lawnmowers;
        float shooterScales[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        std::vector<star> stars;
    };

}   // namespace m1
