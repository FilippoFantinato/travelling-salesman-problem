#include "GavishGraves.h"

GavishGraves::GavishGraves(const TSP& tsp, const std::string& name) : TSPCPXSolver(tsp, name) { }

void GavishGraves::build()
{
    const std::set<Vertex>& vertices = tsp.get_vertices();
    const auto& edges = tsp.get_edges();
    const size_t N = tsp.get_n();
    const Vertex IN = *(vertices.cbegin());

    int current_var = 0;

    // OBJ function
    
    // add y vars [in o.f.: sum[i, j] c_ij yij]
    for(auto edge: edges)
    {
        Vertex i = std::get<0>(edge);
        Vertex j = std::get<1>(edge);
        Weight w = std::get<2>(edge);

        char type = 'B';
        double lb = 0.0;
        double ub = 1.0;
        char *yname = const_cast<char *>(("y_" + std::to_string(i) + "_" + std::to_string(j)).c_str());
        
        map_y[i][j] = current_var;
        ++current_var;

        CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &w, &lb, &ub, &type, &yname);
    }

    // add x vars
    for(auto edge: edges)
    {
        Vertex i = std::get<0>(edge);
        Vertex j = std::get<1>(edge);

        if(j != IN) {
            char type = 'C';
            double lb = 0.0;
            double ub = CPX_INFBOUND;
            char *xname = const_cast<char *>(("x_" + std::to_string(i) + "_" + std::to_string(j)).c_str());
            double obj = 0;

            map_x[i][j] = current_var;
            ++current_var;

            CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &obj, &lb, &ub, &type, &xname);
        }
    }

    // Constraints

    // for all k in N\{0}, sum[i] x_i_k - sum[j!=0] x_k_j = 1
    for(auto& k: vertices)
    {
        if(k != IN)
        {
            std::vector<int> idx;
            std::vector<double> coef;
            char sense = 'E';
            double rhs = 1;
            int matbeg = 0;

            for(auto& i: vertices)
            {
                if(tsp.exist_edge(i, k))
                {
                    idx.push_back(map_x[i][k]);
                    coef.push_back(1.0);
                }
            }

            for(auto& j: vertices)
            {
                if(j != IN && tsp.exist_edge(k, j))
                {
                    idx.push_back(map_x[k][j]);
                    coef.push_back(-1.0);
                }
            }

            CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr, nullptr);
        }
    }

    // for all i in N, sum[j] y_i_j = 1
    for(auto& i: vertices)
    {
        std::vector<int> idx;
        std::vector<double> coef;
        char sense = 'E';
        int matbeg = 0;
        double rhs = 1;

        for(auto& j: vertices)
        {
            if(tsp.exist_edge(i, j))
            {
                idx.push_back(map_y[i][j]);
                coef.push_back(1.0);
            }
        }

        CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr, nullptr);
    }

    // for all j in N, sum[i] y_i_j = 1
    for(auto& j: vertices)
    {
        std::vector<int> idx;
        std::vector<double> coef;
        char sense = 'E';
        int matbeg = 0;
        double rhs = 1;

        for(auto& i: vertices)
        {
            if(tsp.exist_edge(i, j))
            {
                idx.push_back(map_y[i][j]);
                coef.push_back(1.0);
            }
        }

        CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr, nullptr);
    }

    // for all (i,j) in A, x_i_j <= (|N|-1) y_i_j
    for(auto edge: edges)
    {
        Vertex i = std::get<0>(edge);
        Vertex j = std::get<1>(edge);

        if(j != IN)
        {
            std::vector<int> idx{ map_x[i][j], map_y[i][j] };
            std::vector<double> coef{ 1.0, 1-((double)N) };
            char sense = 'L';
            double rhs = 0.0;
            int matbeg = 0;

            CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], nullptr, nullptr);
        }
    }
}

std::shared_ptr<Path> GavishGraves::get_best_cycle() const
{
    auto N = tsp.get_n();
    auto n_vars = N*N - N;
    auto vars = get_vars(n_vars);

    std::map<Vertex, Vertex> successors;

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(i != j && (*vars)[map_y.at(i).at(j)] > 1e-5)
            {
//                std::cout << "Adding: ";
//                std::cout << "(" << i << ", " << j << ") " << (*vars)[map_y.at(i).at(j)] << std::endl;
                successors[i] = j;
            }
        }
    }

    Vertex current = *tsp.get_vertices().cbegin();
    Path best_cycle {current};

    for(int i = 0; i < N-1; ++i)
    {
        Vertex next = successors.at(current);
        best_cycle.push_back(next);
        current = next;
    }

    return std::make_shared<Path>(best_cycle);
}
