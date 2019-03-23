#include "skeleton.h"
#include "splitstring.h"
#include <cmath>

/*
 * Load skeleton file
 */

/*
	MAKE MINOR CHANGES FOR THE STRUCTURE OF THE JOINT TREE
*/
void Skeleton::loadSkeleton(std::string skelFileName)
{
    std::string strBone;
    std::ifstream skelFile(skelFileName.c_str());
    if (skelFile.is_open())
    {
        while ( std::getline(skelFile, strBone)) { //Read a line to build a bone
            std::vector<std::string> boneParams;
            splitstring splitStr(strBone);
            boneParams = splitStr.split(' ');
            Joint temp;
            temp.position.x = std::atof(boneParams[1].c_str());
            temp.position.y = std::atof(boneParams[2].c_str());
            temp.position.z = std::atof(boneParams[3].c_str());

			// Additional Changes
			temp.parentIndex = std::atof(boneParams[4].c_str());
			// std::cout << "PARENT INDEX: " << temp.parentIndex << std::endl;


            if (std::atoi(boneParams[0].c_str()) != joints.size())
            {
                std::cout<<"[Warning!!!] Bone index not match\n";
            }
            joints.push_back(temp);
        }
    }
}

/*
 * Load Animation
 */
void Skeleton::loadAnimation(std::string skelFileName)
{
}


/*
 * Draw skeleton with OpenGL
 */
void Skeleton::glDrawSkeleton()
{
    //Rigging skeleton
    glDisable(GL_DEPTH_TEST);
    
    glPushMatrix();
    glTranslatef(-0.9,-0.9,-0.9);
	glScalef(1.8,1.8,1.8);
	glPointSize(6);
	glColor3f(1,0,0);
    updateScreenCoord();
    
	// Iterates all joints and draws them 
	// ======== SLIGHTLY MODIFY TO ADD SKELETON ========= 

	/*  
		
		=============== ASSIGNMENT PART 1 =============== 

		Given the joints, draw the lines
		
		glBegin(GL_POINTS); 
		glVertex3f(0, 1, 0);
		glVertex3f(0.5, 7, 1.5);
		glVertex3f(5, -2, 1);
		glVertex3f(-2, 0, 2);
		glEnd();

		GL_LINES draws 2 lines (1-2) and (3-4)
		GL_LINE_STRIP draws 3 lines (1-2), (2-3), and (3-4)

		glBegin(GL_LINES);
		glVertex3f(Position of Parent);
		glVertex3f(Position of the Child);
		glEnd();
	*/

    for (unsigned i=0; i<joints.size(); i++)
    {
        if (joints[i].isPicked)
            glColor3f(1.0, 0.0, 0.0);
        else if (joints[i].isHovered)
            glColor3f(0.7, 0.7, 0.7);
        else
            glColor3f(0.3, 0.3, 0.3);

        glTranslated(joints[i].position.x, joints[i].position.y, joints[i].position.z);
        glutSolidSphere(0.01, 15, 15);
        glTranslated(-joints[i].position.x, -joints[i].position.y, -joints[i].position.z);

		// Addition Changes
		if (joints[i].parentIndex != -1) {
			glBegin(GL_LINES);
			glVertex3f(joints[i].position.x, joints[i].position.y, joints[i].position.z);
			glVertex3f(joints[joints[i].parentIndex].position.x,
					   joints[joints[i].parentIndex].position.y,
					   joints[joints[i].parentIndex].position.z);
			glEnd();
		}
		
    }
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST);
}

void Skeleton::updateScreenCoord()
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble winX, winY, winZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    for (unsigned i=0; i<joints.size(); i++)
    {
        gluProject((GLdouble)joints[i].position.x, (GLdouble)joints[i].position.y, (GLdouble)joints[i].position.z,
                modelview, projection, viewport,
                &winX, &winY, &winZ );
        joints[i].screenCoord.x = winX;
        joints[i].screenCoord.y = (double)glutGet(GLUT_WINDOW_HEIGHT)-winY;
    }
}
void Skeleton::checkHoveringStatus(int x, int y)
{
    double distance = 0.0f;
    double minDistance = 1000.0f;
    int hoveredJoint = -1;
    for(unsigned i=0; i < joints.size(); i++)
    {
        joints[i].isHovered = false;
        distance = sqrt((x - joints[i].screenCoord.x)*(x - joints[i].screenCoord.x) 
                + (y - joints[i].screenCoord.y)*(y - joints[i].screenCoord.y));
        if (distance > 50) continue;
        if (distance < minDistance)
        {
            hoveredJoint = i;
            minDistance = distance;
        }
    }
    if (hoveredJoint != -1) joints[hoveredJoint].isHovered = true;
}

void Skeleton::release()
{
    hasJointSelected = false;
    for (unsigned i=0; i<joints.size(); i++)
    {
        joints[i].isPicked = false;
    }
}

void Skeleton::selectOrReleaseJoint()
{
    bool hasHovered=false;
    for (unsigned i=0; i<joints.size(); i++)
    {
        joints[i].isPicked = false;
        if (joints[i].isHovered)
        {
            hasHovered = true;
            joints[i].isPicked = true;
            hasJointSelected = true;
        }
    }
    if (!hasHovered)    //Release joint
        hasJointSelected = false;
}

