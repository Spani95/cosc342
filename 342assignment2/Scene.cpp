/* $Rev: 250 $ */
#include "Scene.h"

#include "Ray.h"
#include "Vector.h"
#include "Point.h"
#include "Colour.h"
#include "Display.h"
#include "utility.h"

Scene::Scene() : backgroundColour(0,0,0), ambientLight(0,0,0), maxRayDepth(3), renderWidth(800), renderHeight(600), filename("render.png"), camera_(), objects_(), lights_() {

}

Scene::~Scene() {

}

void Scene::render() const {
    Display display("Render", renderWidth, renderHeight, Colour(128,128,128));
	
    std::cout << "Rendering a scene with " << objects_.size() << " objects" << std::endl;

    double halfPixel = 2.0/(2*renderWidth);

    for (unsigned int y = 0; y < renderHeight; ++y) {
        for (unsigned int x = 0; x < renderWidth; ++x) {
            double cx = (x - 0.5*renderWidth)*2.0/renderWidth + halfPixel;
            double cy = (y - 0.5*renderHeight)*2.0/renderWidth + halfPixel;
            Ray ray = camera_->castRay(cx,cy);
            display.set(x, y, computeColour(ray, maxRayDepth));
        }
        display.refresh();
    }
    display.save(filename);
    display.pause(5);
}

RayIntersection Scene::intersect(const Ray& ray) const {
    RayIntersection firstHit;
    firstHit.distance = infinity;	
    for (auto& obj : objects_) {
        std::vector<RayIntersection> hits = obj->intersect(ray);
        for (auto& hit : hits) {
            if (hit.distance > epsilon && hit.distance < firstHit.distance) {
                firstHit = hit;
            }
        }
    }
    for (auto& obj: objects_) {
        auto hits = obj->intersect(ray);
    }
    return firstHit;
}

Colour Scene::computeColour(const Ray& viewRay, unsigned int rayDepth) const {
    RayIntersection hitPoint = intersect(viewRay);
    
    if (hitPoint.distance == infinity) {
        return backgroundColour;
    }
    if (rayDepth == 0) {
        return backgroundColour;
    }
    
    Material& mat = hitPoint.material;
        
    Colour hitColour = ambientLight * mat.ambientColour;;

    Normal n = hitPoint.normal;
    Vector normal = n/n.norm();
    Colour specularColour = mat.specularColour;
    Colour diffuseColour = mat.diffuseColour;
        
    for (auto& light : lights_) {
            
        Vector lightDirection = light->location - hitPoint.point;
        lightDirection = lightDirection/lightDirection.norm();

        //shadows
        Ray shadowRay;            
        shadowRay.point = hitPoint.point;
        shadowRay.direction = lightDirection;
        RayIntersection shadowIntersection = intersect(shadowRay);

        //diffuse
        double diffuse = lightDirection.dot(n)/n.norm();

        //specular
        Vector e = -viewRay.direction/viewRay.direction.norm();
        e = 2 * normal * (e.dot(normal)) - e;
        Vector r = lightDirection;
        double specular = pow(e.dot(r), mat.specularExponent);
            
        if (shadowIntersection.distance == infinity) {
            hitColour += light->colour * light->getIntensityAt(hitPoint.point) * diffuse * diffuseColour;
            hitColour += light->colour * light->getIntensityAt(hitPoint.point) * specular * specularColour;
        }
    }

    Vector reflectioin = -viewRay.direction/viewRay.direction.norm();
    reflectioin = 2 * normal * (reflectioin.dot(normal)) - reflectioin;

    Ray reflect;
    reflect.point = hitPoint.point;
    reflect.direction = reflectioin;

    hitColour += mat.mirrorColour * computeColour(reflect, rayDepth - 1);

    hitColour.clip();

    return hitColour;
}

bool Scene::hasCamera() const {
    return bool(camera_);
}
