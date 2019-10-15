#ifndef VECTORMATHS_H
#define VECTORMATHS_H
#include<QVector2D>

class VectorMaths
{
public:
    VectorMaths();
    static QVector2D projectVector(QVector2D vectorToProject, QVector2D axisVector);
    static float getAngle(QVector2D from, QVector2D to);
    static QVector2D crossProduct(QVector2D a, QVector2D b);
};

#endif // VECTORMATHS_H
