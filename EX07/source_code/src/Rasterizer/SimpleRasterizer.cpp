// 7.2 c
// Marek Legris
// Roman Pulgrabja
// Oezcan Oezteke


#include <algorithm>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>

#define RAYTRACER_USE_FOREACH
#include <Raytracer/Raytracer.h>

#include <Rasterizer/SimpleRasterizer.h>

using namespace std;
using namespace glm;
using namespace Rasterizer;
using namespace Raytracer;
using namespace Raytracer::Objects;
using namespace Raytracer::Scenes;

SimpleRasterizer::SimpleRasterizer()
{
	ambientLight = vec3(0.01f);
}

bool SimpleRasterizer::CompareTriangle(const Triangle& t1, const Triangle& t2)
{
	// These aren't actually the mean values, but since both are off by a constant factor (3),
	// this inequation is equivalent.
	return (t1.position[0].z + t1.position[1].z + t1.position[2].z >
		t2.position[0].z + t2.position[1].z + t2.position[2].z);
}

void SimpleRasterizer::DrawSpan(int x1, int x2, int y, float z1, float z2, vec3& color1,
	vec3& color2)
{
	// TODO later exercise sheet
}

void SimpleRasterizer::DrawTriangle(const Triangle& t)
{
	for (int i = 0; i < 3; ++i)
	{
		int x = (int)t.position[i].x;
		int y = (int)t.position[i].y;
		if ((x > 0) && (x < image->GetWidth()) && (y > 0) && (y < image->GetHeight()))
		{
			image->SetPixel(x, y, t.color[i]);
		}
	}
	// TODO later exercise sheet
}

vec3 SimpleRasterizer::LightVertex(vec4 position, vec3 normal, vec3 color)
{
	vec3 result = color * ambientLight;

	foreach(const Light*, light, lights)
	{
		vec3 intensity = vec3(1.0f);
		if ((*light)->IsInstanceOf(SceneObjectType_PointLight))
			intensity = ((PointLight*)*light)->GetIntensity();

		vec3 distance = (*light)->GetPosition() - vec3(position);
		float attenuation = 1.0f / (0.001f + dot(distance, distance));
		vec3 direction = normalize(distance);

		float lambert = glm::max(0.0f, dot(normal, direction));

		if (lambert > 0)
			result += color * lambert * attenuation * intensity;
	}

	return result;
}


void SimpleRasterizer::SortTriangles(vector<Triangle>& triangles)
{
	sort(triangles.begin(), triangles.end(), CompareTriangle);
}


void SimpleRasterizer::TransformAndLightTriangle(Triangle& t,
	const mat4& modelTransform,
	const mat4& modelTransformNormals)
{
	//TODO Exercise 6.2 c)
	// Implement the transformations and lighting of triangle t.
	// Here, use the function LightVertex. The final triangle t should be in world coordinates.
	// Since we render for image, we do not need height or width of image.
	//Implementieren sie die Transformationen und die Beleuchtung des Dreiecks t.
	//Verwenden Sie dazu die Funktion LightVertex.
	//Das fertige Dreieck t soll in Windowkoordinaten vorliegen. Da nach image
	//gerendert wird, brauchen Sie dafür die Höhe und Breite von image.

	// Unanswered EMail (to yaroslav.agapov@iwr.uni-heidelberg.de):
	//
	// After quite some time of searching in the slides,
	// I couldn’t find a suitable example of normalization in 3D Space.
	// This makes me think that we should use the glm implementation of this process.
	// The Problem is that project(...) takes the modelview and the projection matrices,
	// not the model and the projectionview matrices.

	const vec4 viewport(0.0f, 0.0f, image->GetWidth(), image->GetHeight());

	for (size_t i = 0; i < 3; i++)
	{
		const vec4 projected(viewProjectionTransform * modelTransform * vec4(t.position[i], 1));
		const vec3 normal(modelTransformNormals * vec4(t.normal[i], 0));
		const vec3 color(LightVertex(projected, normal, t.color[i]));

		const vec3 normalized(vec3(projected) / projected.w);
		const vec3 viewPosition(viewport * vec4(normalized, 1));

		t.position[i] = viewPosition;
		t.normal[i] = normal;
		t.color[i] = color;
	}
}


void SimpleRasterizer::RenderMesh(const Mesh* mesh)
{
	if (mesh == NULL)
		return;

	mat4x4 modelTransform = mesh->GetGlobalTransformation();
	mat4x4 modelNormalTransform = transpose(inverse(modelTransform));

	for each (auto tri in mesh->GetTriangles())
	{
		TransformAndLightTriangle(tri, modelTransform, modelNormalTransform);
		DrawTriangle(tri);
	}
}

void SimpleRasterizer::ScanObject(const Raytracer::Scenes::SceneObject* object)
{
	if (object == NULL)
		return;

	if (object->IsInstanceOf(SceneObjectType_Light))
		lights.push_back((const Light*)object);
	if (object->IsInstanceOf(SceneObjectType_Mesh))
		meshes.push_back((const Mesh*)object);

	foreach_c(SceneObject*, child, object->GetChildren())
		ScanObject(*child);
}

bool SimpleRasterizer::Render(Image& image, const Scene& scene)
{
	image.Clear(vec3(0));

	Camera* camera = scene.GetActiveCamera();
	if (camera == NULL)
		return false;

	zBuffer = new float[image.GetWidth() * image.GetHeight()];
	for (int i = 0; i < image.GetWidth() * image.GetHeight(); i++)
		zBuffer[i] = 1.0f;

	// Build lists of all lights and meshes in the scene.
	lights.clear();
	meshes.clear();
	ScanObject(&scene);

	// STUDENT START

	mat4x4 viewTransform = camera->GetTransformation();
	mat4x4 projectionTransform = perspective(
		camera->GetFov(),
		camera->GetAspect(),
		camera->GetNearClip(),
		camera->GetFarClip());

	viewProjectionTransform = projectionTransform * viewTransform;

	// STUDENT END

	// Render all meshes we found.
	this->image = &image;
	foreach(const Mesh*, mesh, meshes)
		RenderMesh(*mesh);

	delete[] zBuffer;

	return true;
}