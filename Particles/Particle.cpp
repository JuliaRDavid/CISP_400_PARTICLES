#include "Particle.h"

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
    m_ttl = TTL;
    m_numPoints = numPoints;
    m_radiansPerSec = (float)rand() / (RAND_MAX) * M_PI;

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    m_vx = rand() % 1000 - 500;
    m_vy = rand() % 401 + 100;
    m_color1 = Color{ 0, 0, 0 };
    m_color2 = Color{ static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };

    float theta = static_cast<float>(rand()) / static_cast<float>( (RAND_MAX / (M_PI / 2)));
    float dTheta = 2 * M_PI / (numPoints - 1);

    for (int j = 0; j < numPoints; j++)
    {
        float r = rand() % 60 + 20;
        float dx = r * cos(theta);
        float dy = r * sin(theta);
        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}
void Particle::draw(RenderTarget& target, RenderStates states) const 
{
    VertexArray lines(TriangleFan, m_numPoints + 1);
    Vector2f center = { static_cast<float>(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane).x),
                        static_cast<float>(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane).y) };
    lines[0].position = center;
    lines[0].color = m_color1;

    for (int j = 1; j <= m_numPoints; j++)
    {
        float x = m_A(0, j - 1);
        float y = m_A(1, j - 1);
        lines[j].position = { static_cast<float>(target.mapCoordsToPixel({ x, y }, m_cartesianPlane).x),
                                static_cast<float>(target.mapCoordsToPixel({ x, y }, m_cartesianPlane).y) };
        lines[j].color = m_color2;
    }
    target.draw(lines);
}
void Particle::update(float dt)
{
    m_ttl -= dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    float dx, dy;
    dx = m_vx * dt;
    m_vy -= G * dt;
    dy = m_vy * dt;
    translate(dx, dy);
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
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    RotationMatrix R(theta);
    m_A = R * m_A;
    translate(temp.x, temp.y);
}

///Scale the size of the Particle by factor c
///construct a ScalingMatrix S, left multiply it to m_A
void Particle::scale(double c)
{
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

    ScalingMatrix S(c);
    m_A = S * m_A;
}

///shift the Particle by (xShift, yShift) coordinates
///construct a TranslationMatrix T, add it to m_A
void Particle::translate(double xShift, double yShift)
{
    TranslationMatrix T(xShift, yShift, m_numPoints);
    m_A = T + m_A;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}