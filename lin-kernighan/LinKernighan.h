#ifndef LIN_KERNIGHAN_H
#define LIN_KERNIGHAN_H

#include <unordered_map>
#include <set>
#include <functional>

#include "../libraries/tsp-solvers/TSPSolver.h"
#include "../libraries/tour/Tour.h"
#include "../libraries/graph-functions/compute_cost.h"

struct CmpGainNeighbours {
    bool operator()(
		const std::pair<Vertex, std::vector<double>>& el1, 
		const std::pair<Vertex, std::vector<double>>& el2) const {
        return el1.second[0] > el2.second[0];
    }
};

struct VectorHasher {
	int operator()(const std::vector<Vertex>& v) const {
		int hash = v.size();
		for(auto& i : v) {
			hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		return hash;
	}
};

class LinKernighan : public TSPSolver
{
private:
	std::unordered_map<Vertex, std::vector<double>> neighbours;

	std::unordered_map<std::vector<Vertex>, bool, VectorHasher> solutions;
	std::vector<Vertex> *path = NULL;
	double cost = 0;

	std::multiset<std::pair<Vertex, std::vector<double>>, CmpGainNeighbours> closest(
		const Vertex& v, 
		const Tour& tour, 
		double gain, 
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
	LinKernighan(const TSP& tsp,
                 const std::function<std::vector<Vertex>*(const TSP&)>& initial_path,
                 const std::string& name = "");

	double solve() override;
    void write_file(const std::string& directory = "") override {}
	double get_solution_cost() const;
};

#endif 
