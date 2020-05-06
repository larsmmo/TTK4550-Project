#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#pragma once

#include "sceneGraph.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Terrain
{
private:


public:

};

// FOR TESTING ONLY
/*
void createHeightMap(float noiseWidth, float noiseHeight, float vertWidth, float vertHeight) {
	// Produces 3D ridged multifractal noise, similar to mountains
	module::RidgedMulti baseMountainTerrain;
	module::Voronoi plateauTerrain;

#if 1
	// Generates "Billowy" noise suitable for clouds and rocks?
	module::Billow baseFlatTerrain;
	baseFlatTerrain.SetFrequency(4.0);
#endif

#if 0
	module::Spheres baseFlatTerrain;
	baseFlatTerrain.SetFrequency(2.0);

#endif

#if 0
	// Produces polygon-like formations
	module::Voronoi baseFlatTerrain;
	baseFlatTerrain.SetFrequency(2.0);
	baseFlatTerrain.SetDisplacement(0.25);
#endif

	// Applies a scaling factor to the output value from the source module
	// Scales the flat terrain, adds noise to it
	module::ScaleBias flatTerrain;
	flatTerrain.SetSourceModule(0, baseFlatTerrain);
	flatTerrain.SetScale(0.125); // Default is 1
	flatTerrain.SetBias(-0.75); // Default is 0
	*/
								// Scales the mountain terrain
								// Can use if needed, but not right now
								/*
								module::ScaleBias mountainTerrain;
								mountainTerrain.SetSourceModule(0, baseMountainTerrain);
								mountainTerrain.SetScale(0.75);
								mountainTerrain.SetBias(-0.75); */
	/*
	module::Perlin terrainType;
	
	module::Select terrainSelector;
	terrainSelector.SetSourceModule(0, flatTerrain);
	terrainSelector.SetSourceModule(1, baseMountainTerrain);
	terrainSelector.SetControlModule(terrainType);
	terrainSelector.SetBounds(0.0, 1000); //1000
	terrainSelector.SetEdgeFalloff(0.125); // .125

										   // pseudo-random displacement of the input value
	module::Turbulence finalTerrain;
	finalTerrain.SetSourceModule(0, terrainSelector);
	finalTerrain.SetFrequency(4.0); // How rapidly the displacement changes
	finalTerrain.SetPower(0.125); // The scaling factor that is applied to the displacement amount

								  // Output the noise map
	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(finalTerrain);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(noiseWidth, noiseHeight);
	heightMapBuilder.SetBounds(0, vertWidth, 0, vertHeight);
	heightMapBuilder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);
	renderer.Render();

	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("res/heightmap.bmp");
	writer.WriteDestFile();
}
*/

#endif