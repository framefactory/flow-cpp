// -----------------------------------------------------------------------------
//  File        main.h
//  Project     Tilator
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#include "Tilator/ImageProcessor.h"
#include "Tilator/ViewType.h"
#include "FlowCore/StopWatch.h"

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

// -----------------------------------------------------------------------------

FViewType detectViewType(std::string text)
{
	text = FString::toLower(text);
	if (text.find("front") != string_t::npos)
		return FViewType::OrthographicFront;
	if (text.find("back") != string_t::npos)
		return FViewType::OrthographicBack;
	if (text.find("left") != string_t::npos)
		return FViewType::OrthographicLeft;
	if (text.find("right") != string_t::npos)
		return FViewType::OrthographicRight;
	if (text.find("top") != string_t::npos)
		return FViewType::OrthographicTop;
	if (text.find("bottom") != string_t::npos)
		return FViewType::OrthographicBottom;
	if (text.find("oblique") != string_t::npos)
		return FViewType::OrthographicOblique;
	if (text.find("special") != string_t::npos)
		return FViewType::OrthographicSpecial;

	return FViewType::OrthographicFront;
}

int main(int argc, char *argv[])
{
	po::options_description desc("Allowed options");

	desc.add_options()("help,h", "Show this message")
					  ("input,i", po::value<std::string>(), "input path and prefix")
					  ("output,o", po::value<std::string>(), "output path")
		              ("view,v", po::value<std::string>(), "view type")
					  ("xmin", po::value<float>(), "bounding volume, minimum x-coordinate (width)")
					  ("xmax", po::value<float>(), "bounding volume, maximum x-coordinate (width)")
					  ("ymin", po::value<float>(), "bounding volume, minimum y-coordinate (height)")
					  ("ymax", po::value<float>(), "bounding volume, maximum y-coordinate (height)")
					  ("zmin", po::value<float>(), "bounding volume, minimum z-coordinate (depth)")
					  ("zmax", po::value<float>(), "bounding volume, maximum z-coordinate (depth)")
					  ("tile-size", po::value<int>(), "power of 2 tile size")
					  ("normal,n", po::value<std::string>(), "normal layout, e.g. +X-Y+Z")
					  ("auto-contrast,c", "automatic occlusion contrast normalization")
					  ("save-maps,m", "save full size converted maps")
					  ("save-tiles,t", "save tiled maps")
					  ("rotate,r", "(unused)");

	po::variables_map vm;

	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);  
	}
	catch(po::error e) {
		std::cout << "Argument error: " << e.what() << "\n";
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("help") || !vm.count("input"))
	{
		std::cout << desc << "\n";
		return 1;
	}

	std::cout << std::endl << "----- TILATOR 4.09 -----" << std::endl << std::endl;

	FStopWatch stopWatch;
	stopWatch.start();

	string_t inputPrefix = vm["input"].as<std::string>();
	std::cout << "Input prefix:            " << inputPrefix << std::endl;

	string_t outputPrefix = vm.count("output") ? vm["output"].as<std::string>() : "";
	std::cout << "Output prefix:           " << outputPrefix << std::endl;

	string_t viewText = vm.count("view") ? vm["view"].as<std::string>() : inputPrefix;
	FViewType viewType = detectViewType(viewText);
	std::cout << "View type:               " << viewType.name() << std::endl;
	
	float xmin = vm.count("xmin") ? vm["xmin"].as<float>() : -100.0f;
	float xmax = vm.count("xmax") ? vm["xmax"].as<float>() : 100.0f;
	float ymin = vm.count("ymin") ? vm["ymin"].as<float>() : xmin;
	float ymax = vm.count("ymax") ? vm["ymax"].as<float>() : xmax;
	float zmin = vm.count("zmin") ? vm["zmin"].as<float>() : xmin;
	float zmax = vm.count("zmax") ? vm["zmax"].as<float>() : xmax;
	FVector3f bbMin(xmin, ymin, zmin);
	FVector3f bbMax(xmax, ymax, zmax);
	std::cout << "Bounding Volume, Min:    " << bbMin << std::endl;
	std::cout << "Bounding Volume, Max:    " << bbMax << std::endl;
	
	int tileSize = vm.count("tile-size") ? vm["tile-size"].as<int>() : 512;
	std::cout << "Tile size:               " << tileSize << std::endl;
	
	string_t normalLayout = vm.count("normal")
		? vm["normal"].as<std::string>() : string_t("xzy");
	std::cout << "Normals layout:          " << normalLayout << std::endl;

	bool autoContrast = vm.count("auto-contrast") > 0;
	std::cout << "Contrast normalization:  " << (autoContrast ? "enabled" : "disabled") << std::endl;
	
	bool saveMaps = vm.count("save-maps") > 0;
	std::cout << "Save converted maps:     " << (saveMaps ? "enabled" : "disabled") << std::endl;

	bool saveTiles = vm.count("save-tiles") > 0;
	std::cout << "Save tiles:              " << (saveTiles ? "enabled" : "disabled") << std::endl;

	FImageProcessor processor(viewType);
	bool result = processor.process(
		inputPrefix, outputPrefix, bbMin, bbMax, tileSize,
		normalLayout, autoContrast, saveMaps, saveTiles);

	std::cout << std::endl << "Completed in "
		<< FString::fromUtf(stopWatch.lapse().timecode(10)) << std::endl;

	return result ? 0 : 1;
}

// -----------------------------------------------------------------------------
