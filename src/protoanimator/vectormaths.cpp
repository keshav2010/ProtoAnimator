#include "vectormaths.h"

QVector2D VectorMaths::projectVector(QVector2D vectorToProject, QVector2D axisVector)
{
    axisVector.normalize();

    float dot = vectorToProject.x()*axisVector.x() + vectorToProject.y()*axisVector.y();
    QVector2D a(dot*axisVector.x(), dot*axisVector.y());

    return a;
}

//Returns Angle in degrees between from/to vectors. This is always the smallest Angle.
float VectorMaths::getAngle(QVector2D from, QVector2D to)
{
   qreal denominator = from.length() * to.length();
   if(denominator < 1e-15f)
       return 0;

   qreal dot = QVector2D::dotProduct(from, to)/denominator;

   if(dot < -1) dot=-1;
   else if(dot > 1) dot=1;

   return acos(dot)*57.2958;//RAD2DEG
}
