/*
 * cmdline-parser.h
 *
 *  Created on: 20.05.2017
 *      Author: wadim.mueller
 */

#ifndef INCLUDE_CMDLINE_PARSER_H_
#define INCLUDE_CMDLINE_PARSER_H_

#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"

using namespace cv;

class EstimatorCmdLineParser {
public:
	EstimatorCmdLineParser(char** cmd_options, int num_options);

	int getHeight() const
	{
		return height;
	}

	int getWidth() const
	{
		return width;
	}

	bool isAdjustable() const
	{
		return adjustable;
	}

	const String& getLeftCameraDevice() const
	{
		return leftCameraDevice;
	}

	const String& getRightCameraDevice() const
	{
		return rightCameraDevice;
	}

	const String& getExtrinsicsFileName() const
	{
		return extrinsicsFileName;
	}

	const String& getIntrinsicsFileName() const
	{
		return intrinsicsFileName;
	}

	int getNumOfDisparities(int width, int height) const
	{
		return scale_to_width(numOfDisparities, width, height);
	}

	int getMinimalObjectSize(int width, int height) const
	{
		return scale_to_resolution(minimalObjectSize, width, height);
	}

	double getCalibrationUnit() const
	{
		return calibrationUnit;
	}

	bool isDisparityMap() const
	{
		return disparityMap;
	}

private:
	int scale_to_resolution(int val, int width, int height) const
	{
		double scaled = (double) val * (width * height) / (this->width * this->height);
		return (int) scaled;
	}
	int scale_to_width(int val, int width, int height) const
	{
		double scaled = (double) val * (width) / (this->width);
		return (int) scaled;
	}
	CommandLineParser* parser;
	int height, width;
	bool adjustable, disparityMap;
	String leftCameraDevice, rightCameraDevice;
	String intrinsicsFileName, extrinsicsFileName;
	int numOfDisparities, minimalObjectSize;
	double calibrationUnit;
};



#endif /* INCLUDE_CMDLINE_PARSER_H_ */
