#include "langmuirviewer.h"
#include "color.h"
#include "axis.h"

#include <QDebug>

Axis::Axis(LangmuirViewer &viewer, QObject *parent) :
    SceneObject(viewer, parent)
{
    init();
}

void Axis::init() {
    x_color = QColor::fromRgbF(0.7, 0.7, 1.0, 1.0);
    y_color = QColor::fromRgbF(1.0, 0.7, 0.7, 1.0);
    z_color = QColor::fromRgbF(0.7, 1.0, 0.7, 1.0);
    alength = 1.00;
    aradius = 0.01;

    emit xColorChanged(x_color);
    emit yColorChanged(y_color);
    emit zColorChanged(z_color);
    emit lengthChanged(alength);
    emit radiusChanged(aradius);
}

void Axis::draw() {
    // lighting and color saved
    GLboolean lighting, colorMaterial;
    glGetBooleanv(GL_LIGHTING, &lighting);
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterial);

    // enable lighting
    glEnable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    // x-axis
    qColorToArray4(x_color, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    m_viewer.drawArrow(alength, aradius);
    glPopMatrix();

    // y-axis
    qColorToArray4(y_color, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glRotatef(90.0, 0.0, 1.0, 0.0);
    QGLViewer::drawArrow(alength, aradius);
    glPopMatrix();

    // z-axix
    qColorToArray4(z_color, color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    QGLViewer::drawArrow(alength, aradius);
    glPopMatrix();

    // restore
    if (colorMaterial) {
        glEnable(GL_COLOR_MATERIAL);
    }
    else {
        glDisable(GL_COLOR_MATERIAL);
    }

    if (lighting) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
}

void Axis::setXColor(QColor color)
{
    if (color != x_color) {
        x_color = color;
        emit xColorChanged(x_color);
    }
}

void Axis::setYColor(QColor color)
{
    if (color != y_color) {
        y_color = color;
        emit yColorChanged(y_color);
    }
}

void Axis::setZColor(QColor color)
{
    if (color != z_color) {
        z_color = color;
        emit zColorChanged(z_color);
    }
}

void Axis::setRadius(double value)
{
    if (value != aradius) {
        aradius = value;
        emit radiusChanged(value);
    }
}

void Axis::setLength(double value)
{
    if (value != alength) {
        alength = value;
        emit lengthChanged(value);
    }
}

void Axis::makeConnections()
{
    SceneObject::makeConnections();
    connect(this, SIGNAL(xColorChanged(QColor)), &m_viewer, SLOT(updateGL()));
    connect(this, SIGNAL(yColorChanged(QColor)), &m_viewer, SLOT(updateGL()));
    connect(this, SIGNAL(zColorChanged(QColor)), &m_viewer, SLOT(updateGL()));
    connect(this, SIGNAL(radiusChanged(double)), &m_viewer, SLOT(updateGL()));
    connect(this, SIGNAL(lengthChanged(double)), &m_viewer, SLOT(updateGL()));
}
