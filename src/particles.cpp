#include "particles.hpp"

//// COMPLEX DEFINITION
Complex makeComplex(const double& x, const double& y)
{
    Complex z;

    z.x = x;
    z.y = y;

    return z;
}

Complex makeComplexExp(const double& radius, const double& theta_deg)
{
    return makeComplex(radius*cos(theta_deg*M_PI/180.0), radius*sin(theta_deg*M_PI/180.0));
}

//// COMPLEX OPERATORS
Complex operator+(const Complex& a, const Complex& b)
{
    return makeComplex(a.x+b.x, a.y+b.y);
}

void operator+=(Complex& a, const Complex& b)
{
    a = a + b;
}

Complex operator-(const Complex& a, const Complex& b)
{
    return makeComplex(a.x-b.x, a.y-b.y);
}

void operator-=(Complex& a, const Complex& b)
{
    a = a - b;
}

Complex operator*(const Complex& a, const Complex& b)
{
    return makeComplex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

void operator*=(Complex& a, const Complex& b)
{
    a = a * b;
}

Complex operator*(const Complex& z, const double& lambda)
{
    return makeComplex(z.x*lambda, z.y*lambda);
}

Complex operator*(const double& lambda, const Complex& z)
{
    return z * lambda;
}

void operator*=(Complex& z, const double& lambda)
{
    z = z * lambda;
}

Complex operator/(const Complex& z, const double& lambda)
{
    return z*(1.0/lambda);
}

void operator/=(Complex& z, const double& lambda)
{
    z = z / lambda;
}

//// FUNCTIONS & PROCEDURES
Complex rotateComplex(const Complex& z, const double& theta_deg)
{
    return makeComplexExp(1, theta_deg)*(z-CENTER) + CENTER;
}

int randInt(const int& start, const int& end)
{
    std::random_device rd;
    std::uniform_int_distribution<> dis(start, end);
    return dis(rd);
}

double randDouble(const double& start, const double& end)
{
    std::random_device rd;
    std::uniform_real_distribution<> dis(start, end);
    return dis(rd);
}

Complex randComplex(const double& start, const double& end)
{
    return makeComplex(randDouble(start, end), randDouble(start, end));
}

void makeParticle(Particle& particle, const Complex& pos, const Complex& speed, const float& mass, const int& radius)
{
    particle.pos = pos;
    particle.speed = speed;
    particle.force = ORIGIN;
    particle.mass = mass;
    particle.radius = radius;
}

void updateParticle(Particle& particle)
{
    particle.force = makeComplex(0, 9.80665);

    particle.pos = particle.pos + DT*particle.speed;
    particle.speed = particle.speed + DT*particle.force/particle.mass;

    bool testLeft, testRight, testDown, testUp;
    testLeft = particle.pos.x < particle.radius/2.0;
    testRight = particle.pos.x > DX-particle.radius/2.0;
    testDown = particle.pos.y < particle.radius/2.0;
    testUp = particle.pos.y > DY-particle.radius/2.0;

    if(testLeft)
    {
        ++particle.pos.x;
        particle.speed = FRICTION * makeComplex(-particle.speed.x, particle.speed.y);
    }
    else if(testRight)
    {
        --particle.pos.x;
        particle.speed = FRICTION * makeComplex(-particle.speed.x, particle.speed.y);
    }

    if(testDown)
    {
        ++particle.pos.y;
        particle.speed = FRICTION * makeComplex(particle.speed.x, -particle.speed.y);
    }
    else if(testUp)
    {
        --particle.pos.y;
        particle.speed = FRICTION * makeComplex(particle.speed.x, -particle.speed.y);
    }
}

void makeWorld(World& world, const int& num)
{
    world.num = num;

    const double angle = 360.0/num;
    makeParticle(world.particles[0], CENTER+makeComplex(0, 50), randComplex(-50, 50), 10, randInt(5, 10));

    for(int i = 1 ; i < num ; ++i)
    {
        makeParticle(world.particles[i], rotateComplex(world.particles[i-1].pos, angle), randComplex(-50, 50), 10, randInt(5, 10));
    }
}

void fillCircle(SDL_Renderer* renderer, const Complex& z, const int& radius)
{
    int x = 0, y = radius;
    int a, b, c, d;

    while(x <= radius)
    {
        a = (int)z.x + x;
        b = (int)z.y + y;
        c = (int)z.x - x;
        d = (int)z.y - y;

        SDL_RenderDrawLine(renderer, a, b, a, d);
        SDL_RenderDrawLine(renderer, c, b, c, d);

        ++x;
        y = (int)sqrt(radius*radius - x*x);
    }
}

void drawWorld(SDL_Renderer* renderer, const World& world)
{
    for(int i = 0 ; i < world.num ; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 55+200*world.particles[i].pos.x/DX, 0, 55+200*world.particles[i].pos.y/DY, 255);
        fillCircle(renderer, world.particles[i].pos, world.particles[i].radius);
    }
}

void updateWorld(World& world)
{
    for(int i = 0 ; i < world.num ; ++i)
    {
        updateParticle(world.particles[i]);
    }
}