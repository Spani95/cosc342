/* $Rev: 250 $ */
#include "SceneReader.h"

#include "Camera.h"
#include "PinholeCamera.h"

#include "LightSource.h"
#include "PointLightSource.h"

#include "Object.h"
#include "Sphere.h"
#include "Cone.h"
#include "CSG.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <sstream>

SceneReader::SceneReader(Scene* scene) :
scene_(scene), startLine_(0) {

}

SceneReader::~SceneReader() {

}

void SceneReader::parseTokenBlock(std::queue<std::string>& tokenBlock) {
	std::string blockType = tokenBlock.front();
	tokenBlock.pop();
	if (blockType == "SCENE") {
		parseSceneBlock(tokenBlock);
	} else if (blockType == "CAMERA") {
		parseCameraBlock(tokenBlock);
	} else if (blockType == "OBJECT") {
		parseObjectBlock(tokenBlock);
	} else if (blockType == "LIGHT") {
		parseLightBlock(tokenBlock);
	} else if (blockType == "MATERIAL") {
		parseMaterialBlock(tokenBlock);
	} else {
		std::cerr << "Unexpected block type '" << blockType << "' starting on line " << startLine_ << std::endl;
		exit(-1);
	}
}

void SceneReader::read(const std::string& filename) {

	std::cout << "Reading scene from " << filename << std::endl;

	std::ifstream fin(filename);

	std::string line;
	int lineNumber = 0;
	int objectDepth = 0;
	startLine_ = 0;
	std::queue<std::string> tokenBlock;
	while (std::getline(fin, line)) {
		++lineNumber;
		std::transform(line.begin(), line.end(), line.begin(), toupper);
		std::stringstream strstream(line);
		std::string token;
		while (strstream >> token) {
			if (token[0] == '#') {
				// A comment
				break;
			} else if (token == "OBJECT") {
				objectDepth++;
				tokenBlock.push(token);
			} else if (token == "END") {
				objectDepth--;
				if(objectDepth < 0) {
					objectDepth = 0;
				}
				if(objectDepth){
					tokenBlock.push(token);						
				}else{
					parseTokenBlock(tokenBlock);
				}
			} else {
				if (tokenBlock.size() == 0) {
					startLine_ = lineNumber;
				}
				tokenBlock.push(token);
			}
		}
	}

	if (tokenBlock.size() > 0) {
		std::cerr << "Unexpected end of file in " << filename << std::endl;
		exit(-1);
	}

	fin.close();

}


void SceneReader::parseSceneBlock(std::queue<std::string>& tokenBlock)  {
	while (tokenBlock.size() > 0) {
		std::string token = tokenBlock.front();
		tokenBlock.pop();
		if (token == "AMBIENTLIGHT") {
			scene_->ambientLight = parseColour(tokenBlock);
		} else if (token == "BACKGROUNDCOLOUR") {
			scene_->backgroundColour = parseColour(tokenBlock);
		} else if (token == "RENDERSIZE") {
			scene_->renderWidth = int(parseNumber(tokenBlock));
			scene_->renderHeight = int(parseNumber(tokenBlock));
		} else if (token == "FILENAME") {
			scene_->filename = tokenBlock.front();
			tokenBlock.pop();
			std::string& fname = scene_->filename;
			std::transform(fname.begin(), fname.end(), fname.begin(), tolower);
		} else if (token == "RAYDEPTH") {
			scene_->maxRayDepth = int(parseNumber(tokenBlock));
		} else {
			std::cerr << "Unexpected token '" << token << "' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}
	}
}

double SceneReader::parseNumber(std::queue<std::string>& tokenBlock) {
	std::string token = tokenBlock.front();
	tokenBlock.pop();
	char *endPtr;
	double result = strtod(token.c_str(), &endPtr);
	if (endPtr != token.c_str()+token.length()) {
		std::cerr << "Expected a number but found '" << token << "' in block starting on line " << startLine_ << std::endl;
		exit(-1);
	} 
	return result;
}

Colour SceneReader::parseColour(std::queue<std::string>& tokenBlock) {
	Colour result;
	result.red = parseNumber(tokenBlock);
	result.green = parseNumber(tokenBlock);
	result.blue = parseNumber(tokenBlock);
	return result;
}

void SceneReader::parseCameraBlock(std::queue<std::string>& tokenBlock){
	// Make a new camera
	std::string cameraType = tokenBlock.front();
	tokenBlock.pop();
	std::shared_ptr<Camera> camera;
	if (cameraType == "PINHOLECAMERA") {
		double focalLength = parseNumber(tokenBlock);
		camera = scene_->newCamera<PinholeCamera>(focalLength);
	} else {
		std::cerr << "Unexpected camera type '" << cameraType << "' in block starting on line " << startLine_ << std::endl;
		exit(-1);
	}

	// Parse camera details
	while (tokenBlock.size() > 0) {
		std::string token = tokenBlock.front();
		tokenBlock.pop();
		if (token == "ROTATE") {
			std::string axis = tokenBlock.front(); 
			tokenBlock.pop();
			double angle = parseNumber(tokenBlock);
			if (axis == "X") {
				camera->transform.rotateX(angle);
			} else if (axis == "Y") {
				camera->transform.rotateY(angle);
			} else if (axis == "Z") {
				camera->transform.rotateZ(angle);
			} else {
				std::cerr << "Unexpected axis '" << axis << "' in block starting on line " << startLine_ << std::endl;
				exit(-1);
			}
		} else if (token == "TRANSLATE") {
			double tx = parseNumber(tokenBlock);
			double ty = parseNumber(tokenBlock);
			double tz = parseNumber(tokenBlock);
			camera->transform.translate(tx, ty, tz);
		} else if (token == "SCALE") {
			double s = parseNumber(tokenBlock);
			camera->transform.scale(s);
		} else if (token == "SCALE3") {
			double sx = parseNumber(tokenBlock);
			double sy = parseNumber(tokenBlock);
			double sz = parseNumber(tokenBlock);
			camera->transform.scale(sx, sy, sz);
		} else {
			std::cerr << "Unexpected token '" << token << "' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}

	}

}

void SceneReader::parseLightBlock(std::queue<std::string>& tokenBlock) {

	std::string lightType = tokenBlock.front();
	tokenBlock.pop();
	std::shared_ptr<LightSource> light;
	if (lightType == "POINTLIGHT") {
		light = scene_->newLight<PointLightSource>();
	} else {
		std::cerr << "Unexpected light type '" << lightType << "' in block starting on line " << startLine_ << std::endl;
		exit(-1);
	}

	while (tokenBlock.size() > 0) {
		std::string token = tokenBlock.front();
		tokenBlock.pop();
		if (token == "LOCATION") {
			light->location(0) = parseNumber(tokenBlock);
			light->location(1) = parseNumber(tokenBlock);
			light->location(2) = parseNumber(tokenBlock);
		} else if (token == "COLOUR") {
			light->colour = parseColour(tokenBlock);
		} else {
			std::cerr << "Unexpected token '" << token << "' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}
	}

}

void SceneReader::parseObjectBlock(std::queue<std::string>& tokenBlock) {
	std::string objectType = tokenBlock.front();
	tokenBlock.pop();
	std::shared_ptr<Object> object;
	if (objectType == "SPHERE") {
		object = scene_->newObject<Sphere>();
	} else if (objectType == "CONE") {
		object = scene_->newObject<Cone>();
	} else if (objectType == "CSG") {
		std::string csgType = tokenBlock.front();
		tokenBlock.pop();

		if(csgType != "UNION" && csgType != "INTERSECTION" && csgType != "DIFFERENCE"){
			std::cerr << "Unimplemented CSG operation '"<< csgType <<"' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}
	  
		if(tokenBlock.front() != "OBJECT"){
			std::cerr << "Missing left CSG tree Object in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}
		tokenBlock.pop(); // Object
	  
		std::queue<std::string> obj;
		std::string t;

		int objectDepth;
		objectDepth = 1;
		while( tokenBlock.size()>0 ){
			t = tokenBlock.front();
			if( t == "END" ) {
				objectDepth--;
				if(objectDepth==0)
					break;
			} else if ( t == "OBJECT" ) {
				objectDepth++;
			}
			obj.push(t);
			tokenBlock.pop();
		}
		tokenBlock.pop(); // END

		// Grab left CSG object
		parseObjectBlock(obj);
		std::shared_ptr<Object> left = scene_->objects_.back();
		scene_->objects_.pop_back();

		if(tokenBlock.front() != "OBJECT"){
			std::cerr << "Missing right CSG tree Object in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}
		tokenBlock.pop(); // Object
	  
		objectDepth = 1;
		while( tokenBlock.size()>0 ){
			t = tokenBlock.front();
			if( t == "END" ) {
				objectDepth--;
				if(objectDepth==0)
					break;
			} else if ( t == "OBJECT" ) {
				objectDepth++;
			}
			obj.push(t);
			tokenBlock.pop();
		}
		tokenBlock.pop(); // END

		// Grab right CSG object
		parseObjectBlock(obj);
		std::shared_ptr<Object> right = scene_->objects_.back();
		scene_->objects_.pop_back();

		object = scene_->newObject<CSG>();
		std::shared_ptr<CSG> csgNode = std::static_pointer_cast<CSG>(object);
		csgNode->left = left;
		csgNode->right = right;
		csgNode->setupCSG(csgType);
	} else {
		std::cerr << "Unexpected object type '" << objectType << "' in block starting on line " << startLine_ << std::endl;
		exit(-1);
	}

	// Parse object details
	while (tokenBlock.size() > 0) {
		std::string token = tokenBlock.front();
		tokenBlock.pop();
		if (token == "ROTATE") {
			std::string axis = tokenBlock.front(); 
			tokenBlock.pop();
			double angle = parseNumber(tokenBlock);
			if (axis == "X") {
				object->transform.rotateX(angle);
			} else if (axis == "Y") {
				object->transform.rotateY(angle);
			} else if (axis == "Z") {
				object->transform.rotateZ(angle);
			} else {
				std::cerr << "Unexpected axis '" << axis << "' in block starting on line " << startLine_ << std::endl;
				exit(-1);
			}
		} else if (token == "TRANSLATE") {
			double tx = parseNumber(tokenBlock);
			double ty = parseNumber(tokenBlock);
			double tz = parseNumber(tokenBlock);
			object->transform.translate(tx, ty, tz);
		} else if (token == "SCALE") {
			double s = parseNumber(tokenBlock);
			object->transform.scale(s);
		} else if (token == "SCALE3") {
			double sx = parseNumber(tokenBlock);
			double sy = parseNumber(tokenBlock);
			double sz = parseNumber(tokenBlock);
			object->transform.scale(sx, sy, sz);
		} else if (token == "MATERIAL") {
			std::string materialName = tokenBlock.front();
			tokenBlock.pop();
			auto material = materials_.find(materialName);
			if (material == materials_.end()) {
				std::cerr << "Undefined material '" << materialName << "' in block starting on line " << startLine_ << std::endl;
				exit(1);
			} else {
				object->material = material->second;
			}
		} else if (token == "COLOUR") {
			Colour objColour = parseColour(tokenBlock);
			object->material.ambientColour = objColour;
			object->material.diffuseColour = objColour;
		} else if (token == "AMBIENT") {
			object->material.ambientColour = parseColour(tokenBlock);
		} else if (token == "DIFFUSE") {
			object->material.diffuseColour = parseColour(tokenBlock);
		} else if (token == "SPECULAR") {
			object->material.specularColour = parseColour(tokenBlock);
			object->material.specularExponent = parseNumber(tokenBlock);
		} else if (token == "MIRROR") {
			object->material.mirrorColour = parseColour(tokenBlock);
		} else {
			std::cerr << "Unexpected token '" << token << "' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}

	}
}

void SceneReader::parseMaterialBlock(std::queue<std::string>& tokenBlock) {
	std::string materialName = tokenBlock.front();
	tokenBlock.pop();
	if (materials_.find(materialName) == materials_.end()) {
		materials_[materialName] = Material();
	} else {
		std::cerr << "Warning: duplicate definition of material '" << materialName << "' found in block starting on line " << startLine_ << std::endl;
	}
	Material& material = materials_.find(materialName)->second;

	while (tokenBlock.size() > 0) {
		std::string token = tokenBlock.front();
		tokenBlock.pop();
		if (token == "COLOUR") {
			Colour objColour = parseColour(tokenBlock);
			material.ambientColour = objColour;
			material.diffuseColour = objColour;
		} else if (token == "AMBIENT") {
			material.ambientColour = parseColour(tokenBlock);
		} else if (token == "DIFFUSE") {
			material.diffuseColour = parseColour(tokenBlock);
		} else if (token == "SPECULAR") {
			material.specularColour = parseColour(tokenBlock);
			material.specularExponent = parseNumber(tokenBlock);
		} else if (token == "MIRROR") {
			material.mirrorColour = parseColour(tokenBlock);
		} else {
			std::cerr << "Unexpected token '" << token << "' in block starting on line " << startLine_ << std::endl;
			exit(-1);
		}

	}
}
