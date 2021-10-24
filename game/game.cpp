#include <iostream>
#include "game.hpp"
#include <windows.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

Figure::Figure(double x, double y):
    x_(x),
    y_(y)
{
    dx_ = 10.0 - rand() % 21;
    dy_ = 10.0 - rand() % 21;
    center_to_edge = 0;
}
Figure::~Figure() {};

void Figure::Draw() {};
void Figure::Move()
{
    x_ += dx_;
    y_ += dy_;
};

void Figure::CollideWithBounds() // for symmetrical figures only
{
    if (x_ - center_to_edge <= 0) {
        dx_ = -dx_;
        x_ = center_to_edge;
    }
    if (x_ + center_to_edge >= SCREEN_W) {
        dx_ = -dx_;
        x_ = SCREEN_W - center_to_edge;
    }
    if (y_ - center_to_edge <= 0) {
        dy_ = -dy_;
        y_ = center_to_edge;
    }
    if (y_ + center_to_edge >= SCREEN_H) {
        dy_ = -dy_;
        y_ = SCREEN_H - center_to_edge;
    }
}


Square::Square(double x, double y, double a) :
    Figure( x, y ),
    a_( a )
{
    half = a_ / 2;
    center_to_edge = half;
}
Square::~Square() {};

void Square::Draw()
{
    al_draw_filled_rectangle(x_ - half, y_ - half,
        x_ + half, y_ + half, al_map_rgb(255, 0, 0));
}


Circle::Circle(double x, double y, double r):
    Figure( x, y ),
    r_( r )
{
    center_to_edge = r_;
}
Circle::~Circle() {};

void Circle::Draw()
{
    al_draw_filled_circle(x_, y_, r_, al_map_rgb(0, 255, 0));
}


FigureList::FigureList() :
    size_( 0 )
{
    for (int i = 0; i < MAX_FIGS; ++i) {
        figures[i] = 0;
    }
}

FigureList::~FigureList() {
    for (int i = 0; i < size_; ++i)
    {
        delete figures[i];
        figures[i] = 0;
    }
}

void FigureList::addFig(Figure *fig) {
    if (size_ < MAX_FIGS){
        figures[size_] = fig;
        size_++;
    }
}

void FigureList::generateRandomFigures() {
    size_ = rand() % MAX_FIGS + 1;       
    for (int i = 0; i < size_; ++i)
    {
        if (rand() % 2 == 0) {
            figures[i] = FigureFactory::CreateRandomSquare();
        } else {
            figures[i] = FigureFactory::CreateRandomCircle();
        }
    }
}

void FigureList::nextFrame()
{
    for (int i = 0; i < size_; ++i)
    {
        figures[i]->Move();
        figures[i]->CollideWithBounds();
    }
}

void FigureList::drawAll()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    for (int i = 0; i < size_; ++i)
    {
        figures[i]->Draw();
    }
}

Figure* FigureFactory::CreateRandomSquare() {
    return new Square(rand() % SCREEN_W, rand() % SCREEN_H, rand() % MAX_FIG_SIZE);
}

Figure* FigureFactory::CreateRandomCircle() {
    return new Circle(rand() % SCREEN_W, rand() % SCREEN_H, rand() % MAX_FIG_SIZE);
}

AllegroApp::AllegroApp() {
    srand(time(NULL));
    figureList.generateRandomFigures();
}

AllegroApp::~AllegroApp() {}

AllegroApp& AllegroApp::Instance() {
    static AllegroApp instance;
    return instance;
}

void AllegroApp::Fps()
{
    figureList.nextFrame();
}

void AllegroApp::Draw()
{
    figureList.drawAll();
}


FigureList figureList;
int main(int argc, char** argv)
{
    if (!AllegroApp::Instance().Init(SCREEN_W, SCREEN_H, FPS))
    {
        AllegroApp::Instance().Destroy();
        return 1;
    }

    AllegroApp::Instance().Run();
    return 0;
}
