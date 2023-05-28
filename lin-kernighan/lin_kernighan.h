#ifndef LIN_KERNIGHAN_H
#define LIN_KERNIGHAN_H

#include <set>
#include <stack>

#include "../libraries/tsp/solvers/TSPSolver.h" 
#include "../libraries/tsp/tour/Tour.h"

class LinKernighan : public TSPSolver
{
private:
	std::unordered_map<Vertex, std::vector<double>> neighbours;
	std::unordered_map<std::vector<Vertex>, bool> solutions;
	std::vector<Vertex> path;
	int cost;

	std::unordered_map<Vertex, std::vector<Vertex>> closest(
		const Vertex& v, 
		const Tour& tour, 
		int gain, 
		const std::vector<VertexPair>& broken, 
		const std::vector<VertexPair>& joined);

	bool chooseX(
		const Tour& tour,
		const Vertex& v,
		const Vertex& last,
		double gain,
		const std::vector<VertexPair>& broken,
		const std::vector<VertexPair>& joined);

	bool chooseY(
		const Tour& tour,
		const Vertex& v,
		const Vertex& u,
		double gain,
		const std::vector<VertexPair>& broken,
		const std::vector<VertexPair>& joined);
	
	bool improve();

public:
	LinKernighan(const TSP& tsp);

	double solve() override;
};

#endif 
