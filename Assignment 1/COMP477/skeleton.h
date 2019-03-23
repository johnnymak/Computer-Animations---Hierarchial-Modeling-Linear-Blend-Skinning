#ifndef SKELETON_H
#define SKELETON_H
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include "GL/glut.h"
#else
#include <GL/freeglut.h>
#endif
#endif

#include "simpleMath.h"



struct Joint
{
    Vec3 position;
    Vec2 screenCoord;
    bool isHovered;
    bool isPicked;

	// Additional Changes
	int parentIndex;
    
    Joint()
    {
        isHovered = false;
        isPicked = false;
    }
};

class Skeleton
{
private:
    std::vector<Joint> joints;
    /*Update screen coordinates of joints*/
    void updateScreenCoord();
    
public:
    /*True if the skeleton has a joint selected*/
    bool hasJointSelected;   
    Skeleton(){hasJointSelected = false;};
    /*
     * Load Skeleton file
     */
    void loadSkeleton(std::string skelFileName);

    /*
     * Load animation file
     */
    void loadAnimation(std::string skelFileName);

    /*
     * Draw skeleton with OpenGL
     */
    void glDrawSkeleton();

    /*
     * Check if any joint is hovered by given mouse coordinate
     */
    void checkHoveringStatus(int x, int y);

    void release();
    
    void selectOrReleaseJoint();
};

#endif
