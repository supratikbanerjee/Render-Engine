#pragma once
class Metrics
{
public:
	Metrics();
	float* deltaTime;
	int* verts;
	int* tris;
	int* drawCalls;
	int* setPassCalls;
	unsigned int* vsOut;
	unsigned int* fragOut;
};