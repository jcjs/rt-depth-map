/*
 * bm_sw.cpp
 *
 *  Created on: 02.04.2017
 *      Author: sefo
 */

#include "stereo-matcher/bm-sw.h"

using namespace cv;

SWMatcherKonolige::SWMatcherKonolige(Rect& roi1, Rect& roi2, int preFilterCap, int blockSize, int minDisparity,
		int textureThreshold, int numOfDisparities, int maxDisparity, int uniquenessRatio, int speckleWindowSize,
		int speckleRange, int disp12MaxDiff)
{
	matcher = StereoBM::create(numOfDisparities, blockSize);

	matcher->setPreFilterCap(preFilterCap);
	matcher->setMinDisparity(minDisparity);
	matcher->setNumDisparities(numOfDisparities);
	matcher->setTextureThreshold(textureThreshold);
	matcher->setUniquenessRatio(uniquenessRatio);
	matcher->setSpeckleWindowSize(speckleWindowSize);
	matcher->setSpeckleRange(speckleRange);
	matcher->setDisp12MaxDiff(disp12MaxDiff);
}

SWMatcherKonolige::~SWMatcherKonolige()
{

}

int SWMatcherKonolige::compute(InputArray left, InputArray right, OutputArray out)
{
	matcher->compute(left, right, out);

	return 0;
}

void SWMatcherKonolige::setROI1(Rect roi1)
{
	matcher->setROI1(roi1);
}

void SWMatcherKonolige::setROI2(Rect roi2)
{
	matcher->setROI2(roi2);
}
