#include "Collision.h"

bool Collision::IsCollision(const AABB a, const AABB b) {
    return (a.min.x <= b.max.x && b.min.x <= a.max.x && a.min.y <= b.max.y && b.min.y <= a.max.y && a.min.z <= b.max.z && b.min.z <= a.max.z);
}
