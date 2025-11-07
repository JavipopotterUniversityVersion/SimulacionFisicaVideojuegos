#include "WindGenerator.h"
#include "Particle.h"

void WindGenerator::ApplyForce(const std::list<Particle*>& particles, double t) {
    if (!enabled) return;
	for (auto particle : particles) {
        if (IsPointInsideVolume(particle->getPos())) {
            Vector3 diff = wind_velocity - particle->getVelocity();
            Vector3 forceToAdd = k1 * diff + k2 * abs(diff.magnitude()) * diff;
            particle->addForce(forceToAdd * t);
        }
	}
}

bool WindGenerator::IsPointInsideVolume(const Vector3& posToCheck) {
    Vector3 half(volume.x / 2.0f, volume.y / 2.0f, volume.z / 2.0f);

    return (posToCheck.x >= pos.x - half.x && posToCheck.x <= pos.x + half.x) &&
        (posToCheck.y >= pos.y - half.y && posToCheck.y <= pos.y + half.y) &&
        (posToCheck.z >= pos.z - half.z && posToCheck.z <= pos.z + half.z);
}
