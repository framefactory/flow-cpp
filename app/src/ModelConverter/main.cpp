// -----------------------------------------------------------------------------
//  File        main.h
//  Project     Model Converter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/05/21 $
// -----------------------------------------------------------------------------

#include "ModelProcessor.h"

#include "FlowCore/StopWatch.h"
#include "FlowCore/String.h"

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

// -----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	po::options_description desc("Allowed options");

	desc.add_options()("help,h", "Show this message")
		("input,i", po::value<std::string>(), "input mesh file path")
		("output,o", po::value<std::string>(), "output mesh file path");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);  

	if (vm.count("help") || !vm.count("input") || !vm.count("output"))
	{
		std::cout << desc << "\n";
		return 1;
	}

	std::cout << std::endl << "----- MODEL CONVERTER 1.01 -----" << std::endl << std::endl;

	FStopWatch stopWatch;
	stopWatch.start();

	std::cout << "Input: " << vm["input"].as<std::string>() << std::endl;
	std::cout << "Output: " << vm["output"].as<std::string>() << std::endl;

	string_t inputFilePath = vm["input"].as<std::string>();
	string_t outputFilePath = vm["output"].as<std::string>();

	FModelProcessor processor;
	bool result = processor.process(inputFilePath, outputFilePath);

	if (!result) {
		std::cout << "\nError while importing mesh: " << processor.lastErrorString();
	}

	std::cout << std::endl << "Completed in "
		<< FString::fromUtf(stopWatch.lapse().timecode(10)) << std::endl;

	return 0;
}

// -----------------------------------------------------------------------------
