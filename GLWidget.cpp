/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1

    Instructions:
        See main.cpp for more instructions.

        This file contains the class OpenGL portion of the main window.
**************************************************************************/

#include "GLWidget.h"
#include <iostream>

static QGLFormat createQGLFormat()
{
    // Return a QGLFormat object that tells Qt information about what
    // OpenGL context we would like.
    QGLFormat format(QGL::SampleBuffers);
    if (supportsNewOpenGL())
    {
	// Choose a version of OpenGL that supports vertex array objects and
	// tell it that we do not want support for deprecated functions.
        format.setVersion(3, 3);
        format.setProfile(QGLFormat::CoreProfile);
    }
    return format;
}

GLWidget::GLWidget(QWidget *parent) 
    : QGLWidget(createQGLFormat(), parent)
    , m_is_animating(false)
    , m_animation_frame(0)
    , head_joint_angle(0)
    , beak_joint_angle(0)
    , leftleg_joint_angle(0)
    , rightleg_joint_angle(0)
    , leftfoot_joint_angle(0)
    , rightfoot_joint_angle(0)
    , arm_joint_angle(0)
    , body_joint_angle(0)
    , body_joint_angle1(0)
{
    // Start a timer that will call the timerEvent method every 50ms.
    startTimer(/*milliseconds=*/50);
}

void GLWidget::initializeGL()
{
    m_gl_state.initializeGL();

    // To aid with troubleshooting, print out which version of OpenGL we've
    // told the driver to use.
    std::cout << "Using OpenGL: " << glGetString(GL_VERSION) << std::endl;

    // Copy the data for the shapes we'll draw into the video card's memory.
    square.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    circle.initialize(
	m_gl_state.VERTEX_POSITION_SHADER_LOCATION,
	/*num_circle_segments=*/100);
    head.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    body.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    arm.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);
    upperbeak.initialize(m_gl_state.VERTEX_POSITION_SHADER_LOCATION);

    // Tell OpenGL what color to fill the background to when clearing.
    glClearColor(/*red=*/0.7f, /*green=*/0.7f, /*blue=*/0.9f, /*alpha=*/1.0f);

}

void GLWidget::resizeGL(int width, int height)
{
    // Respond to the window being resized by updating the viewport and
    // projection matrices.

    checkForGLErrors();

    // Setup projection matrix for new window
    m_gl_state.setOrthographicProjectionFromWidthAndHeight(width, height);

    // Update OpenGL viewport and internal variables
    glViewport(0, 0, width, height);
    checkForGLErrors();
}

void GLWidget::timerEvent(QTimerEvent *)
{
    // Respond to a timer going off telling us to update the animation.
    if (!m_is_animating)
        return;

    // increment the frame number.
    m_animation_frame++;

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function to animate the character's joints
    //   Note: Nothing should be drawn in this function!
    //////////////////////////////////////////////////////////////////////////

    // Update joint angles.
    const double body_walk_speed = 0.02;
    double body_walk_t =
        (sin(m_animation_frame * body_walk_speed) + 1.0) / 2.0;
    body_joint_angle = body_walk_t * bw_MIN + (1 - body_walk_t) * bw_MAX;

    const double body_jump_speed = 0.2;
    double body_jump_t =
        (sin(m_animation_frame * body_jump_speed) + 1.0) / 2.0;
    body_joint_angle1 = body_jump_t * bj_MIN + (1 - body_jump_t) * bj_MAX;

    const double head_joint_rot_speed = 0.1;
    double head_joint_rot_t =
        (sin(m_animation_frame * head_joint_rot_speed) + 1.0) / 2.0;
    head_joint_angle = head_joint_rot_t * head_MIN + (1 - head_joint_rot_t) * head_MAX;
    
    const double beak_move_speed = 0.1;
    double beak_joint_rot_t =
        (sin(m_animation_frame * beak_move_speed) + 1.0) / 2.0;
    beak_joint_angle = beak_joint_rot_t * beak_MIN + (1 - beak_joint_rot_t) * beak_MAX;

    const double rightleg_joint_rot_speed = 0.1;
    double rightleg_joint_rot_t =
        (cos(m_animation_frame * rightleg_joint_rot_speed) + 1.0) / 2.0;
    rightleg_joint_angle = rightleg_joint_rot_t * rl_MIN + (1 - rightleg_joint_rot_t) * rl_MAX;

    const double leftleg_joint_rot_speed = 0.1;
    double leftleg_joint_rot_t =
        (sin(m_animation_frame * leftleg_joint_rot_speed+180) + 1.0) / 2.0;
    leftleg_joint_angle = leftleg_joint_rot_t * ll_MIN + (1 - leftleg_joint_rot_t) * ll_MAX;

    const double rightfoot_joint_rot_speed = 0.1;
    double rightfoot_joint_rot_t =
        (sin(m_animation_frame * rightfoot_joint_rot_speed) + 1.0) / 2.0;
    rightfoot_joint_angle = rightfoot_joint_rot_t * rf_MIN + (1 - rightfoot_joint_rot_t) * rf_MAX;

    const double leftfoot_joint_rot_speed = 0.1;
    double leftfoot_joint_rot_t =
        (sin(m_animation_frame * leftfoot_joint_rot_speed+180) + 1.0) / 2.0;
    leftfoot_joint_angle = leftfoot_joint_rot_t * lf_MIN + (1 - leftfoot_joint_rot_t) * lf_MAX;

    const double arm_joint_rot_speed = 0.1;
    double arm_joint_rot_t =
        (sin(m_animation_frame * arm_joint_rot_speed) + 1.0) / 2.0;
    arm_joint_angle = arm_joint_rot_t * arm_MIN + (1 - arm_joint_rot_t) * arm_MAX;

    // Tell this widget to redraw itself.
    update();
}

void GLWidget::paintGL()
{
    // This method gets called by the event handler to draw the scene, so
    // this is where you need to build your scene -- make your changes and
    // additions here.  All rendering happens in this function.

    checkForGLErrors();

    // Clear the screen with the background colour.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    // Setup the model-view transformation matrix stack.
    transformStack().loadIdentity();
    checkForGLErrors();

    //////////////////////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function draw the scene.  This should include function
    //   calls to pieces that apply the appropriate transformation matrices
    //   and render the individual body parts.
    //////////////////////////////////////////////////////////////////////////

    // Draw our hinged object
    const float body_w = 100.0f;
    const float body_l = 200.0f;
    const float leftleg_w = 12.5f;
    const float leftleg_l = 50.0f;
    const float rightleg_w = 12.5f;
    const float rightleg_l = 50.0f;
    const float leftfoot_w = 12.5f;
    const float leftfoot_l = 25.0f;
    const float rightfoot_w = 12.5f;
    const float rightfoot_l = 25.0f;
    const float head_w = 50.0f; 
    const float head_l = 50.0f;
    const float upperbeak_w = 25.0f;
    const float upperbeak_l = 5.5f;
    const float lowerbeak_w = 25.0f;
    const float lowerbeak_l = 5.5f;
    const float arm_w = 25.0f;
    const float arm_l = 50.0f;
    const float radius = 5.0f;

    transformStack().pushMatrix(); // Body push
    
    // Body
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().scale(body_w, body_l);
    m_gl_state.setColor(0, 0.25, 0.5);
    body.draw();
    transformStack().popMatrix(); // Body pop

    transformStack().pushMatrix(); // Arm push    
    
    // Arm
    transformStack().translate(body_w/10, body_l/5);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(arm_joint_angle);
    transformStack().scale(arm_w, arm_l);
    transformStack().translate(0, -0.25); 
    m_gl_state.setColor(1, 0, 0);
    arm.draw();
    transformStack().popMatrix(); // Arm pop

    // Arm joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(body_w/10, body_l/5);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    transformStack().pushMatrix(); // Head push
    transformStack().pushMatrix(); // Lower beak push
    
    // Lower Beak
    transformStack().translate(0, body_l/2);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(head_joint_angle);
    transformStack().scale(lowerbeak_w, lowerbeak_l);
    transformStack().translate(-1.5, 0.25);
    m_gl_state.setColor(1, 1, 0);
    square.draw();
    transformStack().popMatrix(); // Lower beak pop

    transformStack().pushMatrix(); // Upper beak push

    // Upper Beak
    transformStack().translate(0, body_l/2);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(head_joint_angle);
    transformStack().translate(0, beak_joint_angle);
    transformStack().scale(upperbeak_w, upperbeak_l);
    transformStack().translate(-1.5, 2.25);
    m_gl_state.setColor(1, 1, 0);
    upperbeak.draw();
    transformStack().popMatrix(); // Upper beak pop

    // Head
    transformStack().translate(0, body_l/2);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(head_joint_angle);
    transformStack().scale(head_w, head_l);
    transformStack().translate(0, 0.25);
    m_gl_state.setColor(0, 0.5, 1);
    head.draw();
    transformStack().popMatrix(); // Head pop 

    // Head joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(0, body_l/2);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    // Eye
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(0, body_l/2);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(head_joint_angle);
    transformStack().scale(radius, radius);
    transformStack().translate(-2, 3);
    m_gl_state.setColor(0, 0, 0);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    transformStack().pushMatrix(); // Right leg push
    transformStack().pushMatrix(); // Right foot push
   
    // Right foot
    transformStack().translate(body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(rightleg_joint_angle);
    transformStack().rotateInDegrees(90);
    transformStack().translate(-body_l/5, 0); // x,y change
    transformStack().rotateInDegrees(rightfoot_joint_angle);
    transformStack().scale(rightfoot_w, rightfoot_l);
    transformStack().translate(0, 0.5); // x,y change
    m_gl_state.setColor(1, 0.5, 0.5);
    square.draw();
    transformStack().popMatrix(); // Right foot pop

    // Right leg
    transformStack().translate(body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(rightleg_joint_angle); 
    transformStack().scale(rightleg_w, rightleg_l);
    transformStack().translate(0, -0.4);
    m_gl_state.setColor(1, 0, 0);
    square.draw();
    transformStack().popMatrix(); // Right thigh pop

    // Right leg joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    // Right foot joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(rightleg_joint_angle);
    transformStack().translate(0,-body_l/5);
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    transformStack().pushMatrix(); // Left leg push
    transformStack().pushMatrix(); // Left foot push

    // Left foot
    transformStack().translate(-body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(leftleg_joint_angle);
    transformStack().rotateInDegrees(90);
    transformStack().translate(-body_l/5, 0); // x,y change
    transformStack().rotateInDegrees(leftfoot_joint_angle);
    transformStack().scale(leftfoot_w, leftfoot_l);
    transformStack().translate(0, 0.5); // x,y change
    m_gl_state.setColor(1, 0.5, 0.5);
    square.draw();
    transformStack().popMatrix(); // Left foot pop
    
    // Left leg
    transformStack().translate(-body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(leftleg_joint_angle);
    transformStack().scale(leftleg_w, leftleg_l);
    transformStack().translate(0, -0.4);
    m_gl_state.setColor(1, 0, 0);
    square.draw();
    transformStack().popMatrix(); // Left thigh pop
 
    // Left leg joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(-body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    // Left foot joint
    transformStack().pushMatrix(); // Joint push
    transformStack().translate(-body_w/4, -body_l/3);
    transformStack().translate(0, body_joint_angle1); // vertical translation
    transformStack().translate(body_joint_angle, 0); // horizontal translation
    transformStack().rotateInDegrees(leftleg_joint_angle);
    transformStack().translate(0,-body_l/5);
    transformStack().scale(radius, radius);
    m_gl_state.setColor(1, 1, 1);
    circle.draw();
    transformStack().popMatrix(); // Joint pop

    // Execute any GL functions that are in the queue just to be safe
    glFlush();
    checkForGLErrors();
}