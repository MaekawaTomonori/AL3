#include "WorldTransform.h"

#include "MathUtils.h"

void WorldTransform::UpdateMatrix() {
    matWorld_ = MathUtils::MakeAffineMatrix(scale_, rotation_, translation_);

    TransferMatrix();
}
