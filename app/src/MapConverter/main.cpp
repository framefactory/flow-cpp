// -----------------------------------------------------------------------------
//  File        main.h
//  Project     MapConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/01/02 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Image.h"
#include "FlowCore/String.h"
#include "FlowCore/StopWatch.h"
#include "FlowCore/Bit.h"
#include "FlowCore/Setup.h"

#include <FreeImage.h>
#include <boost/program_options.hpp>

#include <string>
#include <iostream>

namespace po = boost::program_options;

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	po::options_description desc("Allowed options");

	desc.add_options()("help,h", "Show this message")
		("input,i", po::value<std::string>(), "input file")
		("output,o", po::value<std::string>(), "output file")
		("quality,q", po::value<int>(), "JPEG compression quality");

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

	std::cout << std::endl << "----- MAP CONVERTER 0.91 -----" << std::endl << std::endl;

	FStopWatch stopWatch;
	stopWatch.start();

	string_t inputFilePath = vm["input"].as<std::string>();
	std::cout << "Input file:  " << inputFilePath << std::endl;

	string_t outputFilePath = vm.count("output") ? vm["output"].as<std::string>() : "";
	std::cout << "Output file: " << outputFilePath << std::endl;

	int jpegQuality = vm.count("quality") ? vm["quality"].as<int>() : 90;
	jpegQuality = fMin(jpegQuality, 100);
	std::cout << "JPEG Compression quality: " << jpegQuality << std::endl;

	FImage sourceImage;
	std::cout << "\nLoading source image from " << inputFilePath << std::endl << std::endl;
	if (!sourceImage.load(FString::toUtf(inputFilePath), FImageFileFormat::TIFF)) {
		std::cout << "\nFailed to load input image." << std::endl;
		return 1;
	}

	uint32_t imageWidth = sourceImage.width();

	// get next smaller or equal power of two width
	uint32_t po2width = FBit::ceilPow2(imageWidth);
	po2width = po2width > imageWidth ? po2width >> 1 : po2width;
	
	while (po2width >= 512) {

		if (po2width != imageWidth) {
			std::cout << "Resize to " << po2width << " x " << po2width << std::endl;
			sourceImage = sourceImage.resize(po2width, po2width);
		}

		FImage finalImage = sourceImage;

		if (sourceImage.type() == FImageType::RGB_UInt16) {
			std::cout << "Convert to 8-bit." << std::endl;
			finalImage = sourceImage.convert(FImageType::RGB_UInt8);
		}
		else if (sourceImage.type() != FImageType::Bitmap) {
			std::cout << "\nSource image must be 16-bit RGB or 8-bit RGB, but is "
				<< sourceImage.type().name() << std::endl;
			return -1;
		}

		FImageFileFormat outFormat;
		int flags;
		if (outputFilePath.find(".jpg") != std::string::npos) {
			outFormat = FImageFileFormat::JPEG;
			flags = jpegQuality + (JPEG_OPTIMIZE | JPEG_BASELINE | JPEG_SUBSAMPLING_444);
		}
		else if (outputFilePath.find(".png") != std::string::npos) {
			outFormat = FImageFileFormat::PNG;
			flags = PNG_Z_BEST_COMPRESSION;
		}

		uint32_t kSize = po2width >> 10;
		std::ostringstream oss;
		oss << outputFilePath.substr(0, outputFilePath.size() - 4)
			<< "-" << kSize << "k" << outputFilePath.substr(outputFilePath.size() - 4);

		std::cout << "Save as " << oss.str() << std::endl << std::endl;
		if (!finalImage.save(FString::toUtf(oss.str()), outFormat, flags)) {
			std::cout << "Failed to save image to " << outputFilePath << std::endl;
			return 1;
		}

		po2width >>= 1;
	}


	std::cout << std::endl << "Completed in "
		<< FString::fromUtf(stopWatch.lapse().timecode(10)) << std::endl;

	return 0;
}

// -----------------------------------------------------------------------------
