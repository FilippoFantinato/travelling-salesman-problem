#include "gavish_graves.h"

void GavishGraves::build()
{
    const std::set<Vertex> vertices = tsp.get_vertices();
    const std::set<Edge *>& edges = tsp.get_edges();
    const int N = tsp.get_n();
    const Vertex IN = *(vertices.cbegin());

    std::map<Vertex, std::map<Vertex, int>> map_x;
    std::map<Vertex, std::map<Vertex, int>> map_y;

    long current_var = 0;

    // OBJ function
    // add y vars [in o.f.: sum[i, j] c_ij yij]
    for(auto edge: edges)
    {
        Vertex i = std::get<0>(*edge);
        Vertex j = std::get<1>(*edge);
        Weight w = std::get<2>(*edge);

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
        Vertex i = std::get<0>(*edge);
        Vertex j = std::get<1>(*edge);

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

            CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
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

        CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
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

        CHECKED_CPX_CALL( CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
    }

    // for all (i,j) in A, x_i_j <= (|N|-1) y_i_j
    for(auto edge: edges)
    {
        Vertex i = std::get<0>(*edge);
        Vertex j = std::get<1>(*edge);

        if(j != IN)
        {
            std::vector<int> idx{ map_x[i][j], map_y[i][j] };
            std::vector<double> coef{ 1.0, 1-((double)N) };
            char sense = 'L';
            double rhs = 0.0;
            int matbeg = 0;

            CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &rhs, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
        }
    }
}
