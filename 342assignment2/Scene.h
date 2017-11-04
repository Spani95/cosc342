/* $Rev: 250 $ */
#pragma once

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <memory>
#include <string>
#include <vector>

#include "Camera.h"
#include "Colour.h"
#include "LightSource.h"
#include "Material.h"
#include "NonCopyable.h"
#include "Object.h"
#include "Ray.h"
#include "RayIntersection.h"

class SceneReader;

/** \file
 * \brief Scene class header file.
 */

/**
 * \brief A Scene to be ray traced.
 *
 * A Scene collects Object, LightSource, and Camera data together for rendering.
 * It also includes basic information about the environment (backgroundColour, ambientLight),
 * the image to be produced (renderWidth, renderHeight, filename), and the maximum number of 
 * reflections to allow (maxRayDepth). 
 *
 * Internally it provides the methods required to render an image, such as intersecting a Ray
 * with the Objects in the Scene, and computing the Colour from a Ray.
 *
 * Scene makes use of std::shared_ptr, which is a 'smart pointer' available in C++ since the 2011
 * revision. These provide a safer alternative to raw pointers, since deallocation is handled
 * automatically. You can treat them mostly like normal pointers though, so if you have a shared 
 * pointer to a Sphere, you can get its properties like this:
 * \code
 * // sphere_ptr is a std::shared_ptr<Sphere>
 * sphere_ptr->transform.rotateX(30);
 * \endcode
 *
 */
class Scene : private NonCopyable  {

public:

	/** \brief Default Scene constructor.
	 * This creates an empty Scene, with a black background and no ambient light.
	 * By default the images are rendered at 800x600 pixel resolution, saved
	 * to \c render.png, and allow for up to 3 reflected rays.
	 */
	Scene();

	/** \brief Scene destructor. */
	~Scene();

	/** \brief Add a new Camera.
	 *
	 * Since there may be different types of Camera, a template is used to 
	 * make this a generic method. A specific type of Camera is created and 
	 * returned, so to create a default PinholeCamera we could use
	 * \code
	 *   Scene scene;
	 *   auto camera = scene.newCamera<PinholeCamera>();
	 * \endcode
	 *
	 * Note that a Scene has only one Camera, so calling newCamera() will
	 * replace any existing camera.
	 * 
	 * \tparam CameraType The type of Camera to add.
	 * \return A \c std::shared_ptr to the newly created Camera.
	 */
	template<typename CameraType>
	std::shared_ptr<CameraType> newCamera() {
		std::shared_ptr<CameraType> cam(new CameraType());
		camera_ = cam;
		return cam;
	}


	/** \brief Add a new Camera with a parameter.
	 *
	 * Some Camera types can take a parameter, such as the focal length of a
	 * PinholeCamera. This method forwards the parameter on to the Camera constructor.
	 * To create a PinholeCamera with a focal length of 1.5 we could use
	 * \code
	 *   Scene scene;
	 *   auto camera = scene.newCamera<PinholeCamera>(1.5);
	 * \endcode
	 * 
	 * \tparam CameraType The type of Camera to add.
	 * \param param A parameter to be passed to the CameraType constructor.
	 * \return A \c std::shared_ptr to the newly created Camera.
	 */
	template<typename CameraType>
	std::shared_ptr<CameraType> newCamera(double param) {
		std::shared_ptr<CameraType> cam(new CameraType(param));
		camera_ = cam;
		return cam;
	}

	/** \brief Add a new Object.
	 *
	 * Since there may be different types of Object, a template is used to 
	 * make this a generic method. A specific type of Object is created and 
	 * returned, so to create a default Sphere we could use
	 * \code
	 *   Scene scene;
	 *   auto sphere = scene.newObject<Sphere>();
	 * \endcode
	 * 
	 * Note that the Scene has a collection of Objects, and there is no 
	 * way to remove an Object once added. 
	 *
	 * \tparam ObjectType The type of Object to add.
	 * \return A \c std::shared_ptr to the newly created Object.
	 */
	template<typename ObjectType> 
	std::shared_ptr<ObjectType> newObject() {
		std::shared_ptr<ObjectType> obj(new ObjectType());
		objects_.push_back(obj);
		return obj;
	}

	/** \brief Add a new LightSource.
	 *
	 * Since there may be different types of LightSource, a template is used to 
	 * make this a generic method. A specific type of LightSource is created and 
	 * returned, so to create a default PointLightSource we could use
	 * \code
	 *   Scene scene;
	 *   auto light = scene.newLight<PointLightSource>();
	 * \endcode
	 * 
	 * Note that the Scene has a collection of LightSources, and there is no 
	 * way to remove an LightSource once added. 
	 *
	 * \tparam LightType The type of LightSource to add.
	 * \return A \c std::shared_ptr to the newly created LightSource.
	 */
	template<typename LightType>
	std::shared_ptr<LightType> newLight() {
		std::shared_ptr<LightType> light(new LightType());
		lights_.push_back(light);
		return light;
	}

    /** \brief Add a new LightSource with a Direction and angle.
	 *
	 * SpotLightSource objects can be created with a given Direction and angle,
	 * and this version of newLight() forwards these parameters on to the constructor.
	 *
	 * \tparam LightType The type of LightSource to add.
	 * \param direction The Direction of the new LightSource.
	 * \param angle The angle of the new LightSource.
	 * \return A \c std::shared_ptr to the newly created LightSource.
	 */
	template<typename LightType>
	std::shared_ptr<LightType> newLight(Direction direction, double angle) {
		std::shared_ptr<LightType> light(new LightType(direction, angle));
		lights_.push_back(light);
		return light;
	}

	/** \brief Render an image of the Scene.
	 * 
	 * This method renders an image of the Scene. The size of the
	 * image is (renderWidth x renderHeight), and it is saved to a file specified by
	 * the Scene's filename property. The format of the file is determined by its
	 * extension. 
	 *
	 * Attempts to render a Scene with no Camera will end badly.
	 */
	void render() const;

	Colour backgroundColour; //!< Colour for any Ray that does not hit an Object.

	Colour ambientLight; //!< Ambient light level and Colour in the Scene.

	unsigned int maxRayDepth; //!< Maximum number of reflected Rays to trace.

	/** \brief Check if the Scene has a Camera.
	 *
	 * To render a scene, a Camera is required. It is possible (although
	 * possibly not interesting) to render a scene with no Object or LightSource.
	 * This method checks to see if there is a Camera.
	 *
	 * \return true if the Scene has a Camera, false otherwise.
	 */
	bool hasCamera() const; 

	unsigned int renderWidth;  //!< Width in pixels of the image to render.
	unsigned int renderHeight; //!< Height in pixels of the image to render.
	std::string filename;      //!< File to save the image to.

private:
	friend class SceneReader;
	std::shared_ptr<Camera> camera_;                     //!< Camera to render the image with.
	std::vector<std::shared_ptr<Object>> objects_;       //!< Collection of Objects in the Scene.
	std::vector<std::shared_ptr<LightSource>> lights_;   //!< Collection of LightSources in the Scene.

	/** \brief Intersect a Ray with the Objects in a Scene
	 *
	 * This intersects the Ray with all of the Objects in the Scene and returns
	 * the first hit. If there is no hit, then a RayIntersection with infinite distance
	 * is returned.
	 *
	 * \param ray The Ray to intersect with the Objects.
	 * \return The first intersection of the Ray with the Scene.
	 */
	RayIntersection intersect(const Ray& ray) const;

	/** \brief Compute the Colour seen by a Ray in the Scene.
	 * 
	 * The Colour seen by a Ray depends on the ligthing, the first Object that it
	 * hits, and the Material properties of that Object. This method performs these
	 * computations and comptues the observed Colour. For some Objects it may be necessary
	 * to cast other Rays to deal with reflections. This can conceivably recurse forever,
	 * so a maximum number of reflections is set.
	 *
	 * If the Ray does not hit any Object, then the Scene's backgroundColour should be 
	 * returned.
	 *
	 * \todo Currently this method only deals with ambient lighting and Material properties.
	 *       It needs to be extended to account for the diffuse, specular, and mirror properties
	 *       of the Material of the Object that is hit. Recall from lectures that the formula for
	 *       a combination of ambient, diffuse, and specular lighting is
	 *       \f[ I = I_ak_a + \sum_j{I_j\left( k_d(\hat{\mathbf{\ell}}_j\cdot\hat{\mathbf{n}}) + k_s(\hat{\mathbf{e}}\cdot\hat{\mathbf{r}}_j)^n \right)},\f]
	 *       where the sum is over the LightSources in the Scene.
	 *       You will also need to cast additional Rays to check for shadows and for reflections.
	 *       The number of recursions made for reflections should be limited by the 
	 *       rayDepth parameter passed to this method.
	 * 
	 * \param viewRay The Ray to intersect with the Objects in the Scene.
	 * \param rayDepth The maximum number of reflection Rays that can be cast.
	 * \return The Colour observed by the viewRay.
	 */
	Colour computeColour(const Ray& viewRay, unsigned int rayDepth = 0) const;

};

#endif
