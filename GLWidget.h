/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the OpenGL portion of the main window.
**************************************************************************/

#ifndef __GLWidget_h__
#define __GLWidget_h__

#include "include_gl.h"
#include "GLState.h"
#include "GLShape.h"
#include <QtOpenGL/QtOpenGL>

// Before transformed, this class displays a unit square centered at the
// origin.
class UnitSquare : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
	// Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
	    shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
	    GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

// Before transformed, this class displays a unit circle centered at the
// origin.
class UnitCircle : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location, int num_circle_segments)
    {
        // We will draw a circle as a triangle fan.  We are careful to send
	// the second coordinate twice to properly close the circle.
        //        3     2     1
        //         +----+----+
        //        / \   |   /
        //       /   \  |  /
        //      /     \ | /
        //     /       \|/
        //   4+---------+ 0
        //        ...
        std::vector<GLfloat> circle_vertices;
        circle_vertices.push_back(0.0);
        circle_vertices.push_back(0.0);
        for (int i=0; i<=num_circle_segments; ++i)
        {
            double angle = (2 * M_PI * i) / num_circle_segments;
            circle_vertices.push_back(cos(angle));
            circle_vertices.push_back(sin(angle));
        }

        initialize(
	    shader_input_location,
            &circle_vertices[0],
            num_circle_segments + 2,
	    GL_TRIANGLE_FAN);
    }
};

class Head : public GLShape
{
    public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.3 },  // Triangle 1
            {  0.5, -0.3 },
            {  0.4,  0.3 },
            { -0.5, -0.3 },  // Triangle 2
            {  0.4,  0.3 },
            { -0.4,  0.3 },
            { -0.4,  0.3 },  // Triangle 3
            {  0.4,  0.3 },
            { -0.2,  0.5 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/9,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

class Body : public GLShape
{
    public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.3 },  // Triangle 1
            {  0.5, -0.3 },
            {  0.2,  0.5 },
            { -0.5, -0.3 },  // Triangle 2
            {  0.2,  0.5 },
            { -0.2,  0.5 },
            {  0.5, -0.3 },  // Triangle 3
            { -0.5, -0.3 },
            { -0.1, -0.5 },
            {  0.5, -0.3 },  // Triangle 4
            { -0.1, -0.5 },
            {  0.1, -0.5 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/12,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

class Arm : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.3, -0.5 },  // Triangle 1
            {  0.3, -0.5 },
            {  0.5,  0.5 },
            { -0.3, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0.5 },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

class Upperbeak : public GLShape
{
public:
    using GLShape::initialize;

    void initialize(int shader_input_location)
    {
    // Use two triangles to create the square.
        GLfloat square_vertices[][2] =
        {
            { -0.5, -0.5 },  // Triangle 1
            {  0.5, -0.5 },
            {  0.5,  0.5 },
            { -0.5, -0.5 },  // Triangle 2
            {  0.5,  0.5 },
            { -0.5,  0   },
        };

        initialize(
        shader_input_location,
            reinterpret_cast<const GLfloat *>(square_vertices),
            /*num_vertices=*/6,
        GL_TRIANGLES); // Each group of three coordinates is a triangle
    }
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    // These values control the bounds to display on the joint angle sliders.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Add different ranges for the different joints.  Use these ranges
    //   when constructing sliders and when animating joints.
    //////////////////////////////////////////////////////////////////////////
    static const int head_MIN = -5.625;
    static const int head_MAX = 5.625;
    static const int beak_MIN = -5.625;
    static const int beak_MAX = 0.703125;
    static const int rl_MIN = -22.5;
    static const int rl_MAX = 22.5;
    static const int ll_MIN = -22.5;
    static const int ll_MAX = 22.5;
    static const int rf_MIN = -22.5;
    static const int rf_MAX = 22.5;
    static const int lf_MIN = -22.5;
    static const int lf_MAX = 22.5;
    static const int arm_MIN = -45;
    static const int arm_MAX = 45;
    static const int bw_MIN = -90;
    static const int bw_MAX = 90;
    static const int bj_MIN = -5.625;
    static const int bj_MAX = 5.625;
    GLWidget(QWidget *parent=NULL);

public slots:
    // This method is called when the user changes the joint angle slider.
    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   There is currently only one joint, but you need to add more.
    //////////////////////////////////////////////////////////////////////////
    void setHeadJointAngle(int angle)
    {
        // This method is called when the user changes the slider value.
        head_joint_angle = angle;
        // Call update() to trigger a redraw.
        update();
    }
    void setBeakJointAngle(int angle)
    {
        beak_joint_angle = angle;
        update();
    }
    void setRightLegJointAngle(int angle)
    {
        rightleg_joint_angle = angle;
        update();
    }
    void setLeftLegJointAngle(int angle)
    {
        leftleg_joint_angle = angle;
        update();
    }
    void setRightFootJointAngle(int angle)
    {
        rightfoot_joint_angle = angle;
        update();
    }
    void setLeftFootJointAngle(int angle)
    {
        leftfoot_joint_angle = angle;
        update();
    }
    void setArmJointAngle(int angle)
    {
        arm_joint_angle = angle;
        update();
    }
    void setBodyWalkJointAngle(int angle)
    {
        body_joint_angle = angle;
        update();
    }
    void setBodyJumpJointAngle(int angle)
    {
        body_joint_angle1 = angle;
        update();
    }

    void onPressAnimate(int is_animating)
    {
        // This method is called when the user changes the animation checkbox.
        m_is_animating = (bool)is_animating;
        m_animation_frame = 0;
        update();
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void timerEvent(QTimerEvent *event);

private:
    GLTransformStack &transformStack()
    { return m_gl_state.transformStack(); }

private:
    GLState m_gl_state;
    bool m_is_animating;
    int m_animation_frame;
    UnitSquare square;
    UnitCircle circle;
    Head head;
    Body body;
    Arm arm;
    Upperbeak upperbeak;
    //////////////////////////////////////////////////////////////////////////
    // TODO: Add additional joint parameters.
    //////////////////////////////////////////////////////////////////////////
    double head_joint_angle;
    double beak_joint_angle;
    double rightleg_joint_angle;
    double leftleg_joint_angle;
    double rightfoot_joint_angle;
    double leftfoot_joint_angle;
    double arm_joint_angle;
    double body_joint_angle;
    double body_joint_angle1;
};

#endif
