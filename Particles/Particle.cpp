#include "Particle.h"

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    m_ttl = TTL;
    m_numPoints = numPoints;
    m_radiansPerSec = (float)rand() / (RAND_MAX) * M_PI;

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
    m_centerCoordinate = target.mapCoordsToPixel(mouseClickPosition, m_cartesianPlane);
}
void Particle::draw(RenderTarget& target, RenderStates states) const 
{

}
void Particle::update(float dt)
{

}


//Functions for unit testing
bool Particle::almostEqual(double a, double b, double eps = 0.0001)
{

}
void Particle::unitTests()
{

}

///rotate Particle by theta radians counter-clockwise
    ///construct a RotationMatrix R, left mulitply it to m_A
void Particle::rotate(double theta)
{

}

///Scale the size of the Particle by factor c
///construct a ScalingMatrix S, left multiply it to m_A
void Particle::scale(double c)
{

}

///shift the Particle by (xShift, yShift) coordinates
///construct a TranslationMatrix T, add it to m_A
void Particle::translate(double xShift, double yShift)
{

}