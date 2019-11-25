// Marek Legris
// Roman Pulgrabja
// Özcan Özteke

#include <Raytracer/Raytracer.h>

using namespace Raytracer;
using namespace Raytracer::Scenes;

PointLight::PointLight(const float3 &position, const float3 &intensity)
{
  this->position = position;
  this->intensity = intensity;
}

float3 PointLight::ComputeDirectContribution(const Intersection &intersection, const Scene &scene)
{
	float3 I(0, 0, 0);
	float3 Il = intensity * powf(.5f, distance(position, intersection.position));

	float3 L = normalize(position - intersection.position);
	float NdotL = dot(intersection.normal, L);

	if (NdotL > 0)
	{
		I += intersection.material->GetDiffuse() * Il * NdotL;

		float3 R = 2.f * intersection.normal * NdotL - L;
		float RdotV = dot(R, intersection.viewDirection);
		if (RdotV > 0)
			I += intersection.material->GetSpecular() * Il * powf(RdotV, intersection.material->GetShininess());
	}

	return I;
}
