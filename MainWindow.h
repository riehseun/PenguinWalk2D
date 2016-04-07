/*************************************************************************
    CSC418/2504, Winter 20l5
    Assignment 1
  
  
    Instructions:
        See main.cpp for more instructions.

        This file contains the class for the main window of the program.
**************************************************************************/

#ifndef __MainWindow_h__
#define __MainWindow_h__

#include <QtGui/QtGui>
#include "GLWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow()
    {
        // Create a GLWidget to hold the OpenGL viewport.
        m_gl_widget = new GLWidget();

        // Create a checkbox to turn animation on and off, and make it
        // call GLWidget::onPressAnimate when checked.
        m_animate_checkbox = new QCheckBox("Animate", this);
        connect(
            m_animate_checkbox, SIGNAL(stateChanged(int)),
            m_gl_widget, SLOT(onPressAnimate(int)));

        // Create a button to quit the program.
        m_quit_button = new QPushButton("Quit", this);
        connect(
            m_quit_button, SIGNAL(clicked(bool)),
            this, SLOT(onPressQuit(bool)));

        m_main_layout = new QVBoxLayout();
        m_main_layout->addWidget(m_gl_widget);

        // Create a slider to control the joint angle, and make it call
        // GLWidget::setJointAngle when the slider value changes.
        m_slider = create_joint_angle_slider(
	    "Head joint", GLWidget::head_MIN, GLWidget::head_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setHeadJointAngle(int)));

        //////////////////////////////////////////////////////
        // TODO: Add additional joint sliders here
        //////////////////////////////////////////////////////
        m_slider = create_joint_angle_slider(
        "Beak joint", GLWidget::beak_MIN, GLWidget::beak_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setBeakJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Right Leg joint", GLWidget::rl_MIN, GLWidget::rl_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setRightLegJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Left Leg joint", GLWidget::ll_MIN, GLWidget::ll_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setLeftLegJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Right Foot joint", GLWidget::rf_MIN, GLWidget::rf_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setRightFootJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Left Foot joint", GLWidget::lf_MIN, GLWidget::lf_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setLeftFootJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Arm joint", GLWidget::arm_MIN, GLWidget::arm_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setArmJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Body Walk joint", GLWidget::bw_MIN, GLWidget::bw_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setBodyWalkJointAngle(int)));
        m_slider = create_joint_angle_slider(
        "Body Jump joint", GLWidget::bj_MIN, GLWidget::bj_MAX);
        connect(
            m_slider, SIGNAL(valueChanged(int)),
            m_gl_widget, SLOT(setBodyJumpJointAngle(int)));

        m_main_layout->addWidget(m_animate_checkbox);
        m_main_layout->addWidget(m_quit_button);
        setLayout(m_main_layout);

        m_slider->setValue(0);
        setWindowTitle("CSC418/2504 Assignment 1");
    }

public slots:
    void onPressQuit(bool)
    {
        exit(0);
    }

private:
    QSlider *create_joint_angle_slider(
	const char *label, int min_angle, int max_angle)
    {
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(min_angle, max_angle);
        slider->setSingleStep(1);
        slider->setPageStep(5);
        slider->setTickInterval(5);
        slider->setTickPosition(QSlider::TicksBelow);

	QBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(new QLabel(label));
	layout->addWidget(slider);
	m_main_layout->addLayout(layout);

        return slider;
    }

    GLWidget *m_gl_widget;
    QCheckBox *m_animate_checkbox;
    QPushButton *m_quit_button;
    QSlider *m_slider;
    QVBoxLayout *m_main_layout;
};

#endif
