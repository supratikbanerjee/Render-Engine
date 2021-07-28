#pragma once
class Metrics
{
public:
	Metrics();
	float* deltaTime = 0;
	float* verts = 0;
	float* tris = 0;
	int* drawCalls = 0;
	int* setPassCalls = 0;
	int* vsOut = 0;
	int* fragOut = 0;
};