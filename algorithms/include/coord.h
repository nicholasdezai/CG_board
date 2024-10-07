//
// Created by jin on 24-10-6.
//

#ifndef COORD_H
#define COORD_H

#include <QMatrix4x4>

// 平移坐标变换
QVector4D translation(QVector4D HCTVec,QMatrix4x4 TMat);

// 旋转坐标变换
QVector4D rotation(QVector4D HCTVec,QMatrix4x4 RMat);

#endif //COORD_H
