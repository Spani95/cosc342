/* $Rev: 250 $ */
#include "SceneReader.h"

#include <iostream>
#include <memory>
#include <vector>

/** \file
 * \brief Main file for the ray tracer program.
 */

/** \brief Create a Scene, read input from files, and render the Scene.
 *
 * The main function creates an empty Scene then uses a SceneReader
 * to add information based on input files specified as command line
 * arguments. Multiple scene files can be specified, and they are read
 * in the order provided.
 *
 * The scene is then rendered and saved to file, as long as there
 * is a Camera specified.
 * 
 */
int main (int argc, char *argv[]) {

	Scene scene;
	
	SceneReader reader(&scene);
	
	for (int i = 1; i < argc; ++i) {
		reader.read(argv[i]);
	}

	if (scene.hasCamera()) {
		scene.render();
	} else {
		std::cerr << "Cannot render a scene with no camera!" << std::endl;
	}

	return 0;
}
