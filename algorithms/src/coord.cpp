//
// Created by jin on 24-10-7.
//
#include "coord.h"

QVector4D translation(QVector4D HCTVec,QMatrix4x4 TMat)
{
    QVector4D result;
    result = TMat * HCTVec;
    return result;
}

QVector4D rotation(QVector4D HCTVec,QMatrix4x4 RMat)
{
    QVector4D result;
    result = RMat * HCTVec;
    return result;
}