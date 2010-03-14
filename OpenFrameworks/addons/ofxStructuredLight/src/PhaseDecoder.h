#pragma once

#include "DepthDecoder.h"
#include "FastBlur.h"
#include "PhaseConstants.h"

class PhaseDecoder : public DepthDecoder {
public:
	PhaseDecoder();
	virtual ~PhaseDecoder();
	void setGamma(float gamma);
	void setDepthScale(float depthScale);
	void setDepthSkew(float depthSkew);
	void setOrientation(phaseOrientation orientation);
	void setMaxPasses(int maxPasses);
	void setMinRemaining(float minRemaining);
	void setPhasePersistence(bool phasePersistence);
	void clearLastPhase();
	void set(int i, byte* image, int channels = 3);
	void makeDepth();
	void decode();
	float* getPhase();
	float* getWrappedPhase();
	byte* getColor();
	byte** getGraySequence();
	int* getBlur();
	void exportCloud(string filename);
	void exportMesh(string filename);
	void exportTexture(string filename);
protected:
	byte** colorSequence;
	byte** graySequence;
	float* phase;
	float* wrappedPhase;
	bool* ready;
	byte* color;
	int sequenceSize;
	float gamma;
	int maxPasses;
	float minRemaining;
	float depthScale, depthSkew;
	phaseOrientation orientation;
	FastBlur blur;
	bool phasePersistence;
	float* lastPhase;
	float* range;

	/// this is where phase unwrapping begins, and unwrapped phase will be zero
	int startInd;

	void setup(int width, int height, int sequenceSize);
	virtual void makePhase() = 0;
	virtual void unwrapPhase() = 0;
	virtual void makeColor() = 0;
	virtual int getStart();
	float getRemaining();
};
