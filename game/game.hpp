#pragma once

#include "AllegroBase.hpp"

const int MAX_FIGS = 10;
const int MAX_FIG_SIZE = 75;

class Figure {
protected:
    double x_;
    double y_;
    double dx_;
    double dy_;
    double center_to_edge;

public:
    Figure(double x, double y);
    virtual ~Figure();

    virtual void Draw();
    virtual void Move();
    virtual void CollideWithBounds();
};

class Square : public Figure
{
protected:
    double a_;
    double half;
public:
    Square(double x, double y, double a);
    virtual ~Square();

    virtual void Draw();
};

class Circle : public Figure
{
protected:
    double r_;
public:
    Circle(double x, double y, double r);
    virtual ~Circle();

    virtual void Draw();
};

class FigureList
{
private:
    Figure* figures[MAX_FIGS];
    int size_;

public:
    FigureList();
    virtual ~FigureList();

    void addFig(Figure* fig);
    void generateRandomFigures();
    void nextFrame();
    void drawAll();
};

class FigureFactory
{
public:
    static Figure* CreateRandomSquare();
    static Figure* CreateRandomCircle();
};

class AllegroApp : public AllegroBase
{
private:
    AllegroApp();
    virtual ~AllegroApp();
    FigureList figureList;

public:
    static AllegroApp& Instance();

    virtual void Fps();
    virtual void Draw();
};