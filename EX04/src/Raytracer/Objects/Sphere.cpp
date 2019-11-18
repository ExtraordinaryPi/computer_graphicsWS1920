#include <Raytracer/Raytracer.h>

using namespace Raytracer;
using namespace Raytracer::Scenes;
using namespace Raytracer::Objects;

Sphere::Sphere(const float3 &center, float radius)
{
	this->center = center;
	this->radius = radius;
	this->radius2 = radius * radius;
	this->material = NULL;
}

Sphere::Sphere(const float3 &center, float radius, Material *material)
{
	this->center = center;
	this->radius = radius;
	this->radius2 = radius * radius;
	this->material = material;
}

void Sphere::GetExtent(float3 &min, float3 &max) const
{
	min = center - radius;
	max = center + radius;
};

void Sphere::GetIntersection(const Ray &ray, float distance, Intersection &intersection) const
{
	// DONE: Determine position, viewing direction, normals, and material at the intersection point 
	// of the given ray and the given distance.
	// I.e., insert those values into the intersection struct (3rd parameter)
	// The parameter "distance" (2nd parameter) contains the distance to the ray origin - intersection point.

	float3 hitPoint = ray.GetOrigin() + distance * ray.GetDirection();

	intersection.position = hitPoint;
	intersection.viewDirection = ray.GetDirection();
	intersection.normal = (hitPoint - center) / radius;
	intersection.material = material;
}

bool Sphere::HitTest(const Ray &ray, RayHit &hit) const
{
	hit.Set(&ray, 0, NULL);
	// DONE: Implement the intersection. If the ray hits the sphere set "hit = this;", 
	// set the distance to the next intersection point, and return true (see class RayHit).

	float a = dot(ray.GetDirection(), ray.GetDirection());
	float b = 2 * dot(ray.GetDirection(), ray.GetOrigin() - center);
	float c = dot(ray.GetOrigin() - center, ray.GetOrigin() - center) - radius2;

	if (b * b - 4 * a * c < 0)
		return false;

	// save the sqrt calculation so it gets computed only once;
	float x = sqrtf(b * b - 4 * a * c);

	float t1 = (-b + x) / (2 * a);
	float t2 = (-b - x) / (2 * a);

	float distance = min(t1, t2);
	if (distance < 0)
		distance = max(t1, t2);
	if (distance < 0)
		return false;

	hit.Set(&ray, distance, this);
	return true;
}
