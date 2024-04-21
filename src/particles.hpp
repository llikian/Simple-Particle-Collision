#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include <SDL2/SDL.h>
#include <random>
#include <iostream>

#define DX 1200
#define DY 700
#define MAX_PARTICLES 1000
#define CENTER makeComplex(DX/2.0, DY/2.0)
#define ORIGIN makeComplex(0, 0)
#define DT 0.01
#define FRICTION 0.9

typedef struct
{
    double x, y;
} Complex;

typedef struct
{
    Complex pos, speed, force;
    float mass;
    int radius;
} Particle;

typedef struct
{
    Particle particles[MAX_PARTICLES];
    int num;
} World;

Complex makeComplex(const double& x, const double& y);
Complex makeComplexExp(const double& radius, const double& theta_deg);

Complex operator+(const Complex& a, const Complex& b);
void operator+=(Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
void operator-=(Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
void operator*=(Complex& a, const Complex& b);
Complex operator*(const Complex& z, const double& x);
Complex operator*(const double& x, const Complex& z);
void operator*=(Complex& z, const double& x);
Complex operator/(const Complex& z, const double& x);
void operator/=(Complex& z, const double& x);

Complex rotateComplex(const Complex& z, const double& theta_deg);

int randInt(const int& start, const int& end);
double randDouble(const double& start, const double& end);
Complex randComplex(const double& start, const double& end);

void makeParticle(Particle& particle, const Complex& pos, const Complex& speed, const float& mass, const int& radius);
void updateParticle(Particle& particle);

void makeWorld(World& world, const int& num);
void drawWorld(SDL_Renderer* renderer, const World& world);
void updateWorld(World& world);

void fillCircle(SDL_Renderer* renderer, const Complex& z, const int& radius);

#endif