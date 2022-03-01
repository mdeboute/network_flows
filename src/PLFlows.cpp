#include "PLFlows.hpp"
#include "Graph.hpp"
#include "gurobi_c++.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cstdint>
#include <climits>

namespace PL
{

	int maxFlow(Graph &graph)
	{
		return maxFlow(graph, false);
	}

	int maxFlow(Graph &graph, bool verbose)
	{
		GRBVar *f;
		GRBVar v;
		int result = -1;
		try
		{
			if (verbose)
				std::cout << "--> Creating the Gurobi environment" << std::endl;
			GRBEnv env = GRBEnv(true);
			env.start();
			if (verbose)
				std::cout << "--> Creating the Gurobi model" << std::endl;
			GRBModel model = GRBModel(env);
			if (not verbose)
			{
				model.set(GRB_IntParam_OutputFlag, 0);
			}

			if (verbose)
				std::cout << "--> Creating the variables" << std::endl;
			f = new GRBVar[graph.nbEdges];
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				std::stringstream ss;
				ss << "f(" << i << ")";
				f[i] = model.addVar(0.0, INT_MAX, 0.0, GRB_CONTINUOUS, ss.str());
			}
			v = model.addVar(0.0, INT_MAX, 0.0, GRB_CONTINUOUS, "v");

			if (verbose)
				std::cout << "--> Creating the objective function" << std::endl;
			GRBLinExpr obj = v;
			model.setObjective(obj, GRB_MAXIMIZE);

			if (verbose)
				std::cout << "--> Creating the constraints" << std::endl;
			// flot entrant = flot sortant
			for (size_t i = 0; i < graph.nbVertices; ++i)
			{
				if (i != graph.src && i != graph.sink)
				{
					GRBLinExpr lhs = 0;
					for (size_t j = 0; j < graph.vertices[i].nbEnteringEdges; ++j)
					{
						lhs += f[graph.vertices[i].enteringEdgesId[j]];
					}
					for (size_t j = 0; j < graph.vertices[i].nbLeavingEdges; ++j)
					{
						lhs -= f[graph.vertices[i].leavingEdgesId[j]];
					}
					std::stringstream ss;
					ss << "Flow(" << i << ")";
					model.addConstr(lhs == 0, ss.str());
				}
			}
			// flot de s
			GRBLinExpr lhsS = 0;
			for (size_t j = 0; j < graph.vertices[graph.src].nbLeavingEdges; ++j)
			{
				lhsS += f[graph.vertices[graph.src].leavingEdgesId[j]];
			}
			for (size_t j = 0; j < graph.vertices[graph.src].nbEnteringEdges; ++j)
			{
				lhsS -= f[graph.vertices[graph.src].enteringEdgesId[j]];
			}
			lhsS -= v;
			std::stringstream ssS;
			ssS << "Flow(" << graph.src << ")";
			model.addConstr(lhsS == 0, ssS.str());
			// flot de t
			GRBLinExpr lhsT = 0;
			for (size_t j = 0; j < graph.vertices[graph.sink].nbLeavingEdges; ++j)
			{
				lhsT += f[graph.vertices[graph.sink].leavingEdgesId[j]];
			}
			for (size_t j = 0; j < graph.vertices[graph.sink].nbEnteringEdges; ++j)
			{
				lhsT -= f[graph.vertices[graph.sink].enteringEdgesId[j]];
			}
			lhsT += v;
			std::stringstream ssT;
			ssT << "Flow(" << graph.sink << ")";
			model.addConstr(lhsT == 0, ssT.str());

			// respect des capacités
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				GRBLinExpr lhs = f[i] - graph.edges[i].maxCapacity;
				std::stringstream ss;
				ss << "Capacity(" << i << ")";
				model.addConstr(lhs <= 0, ss.str());
			}

			// Optimize model
			// --- Solver configuration ---
			if (verbose)
				std::cout << "--> Configuring the solver" << std::endl;
			model.set(GRB_DoubleParam_TimeLimit, 600.0); //< sets the time limit (in seconds)
			model.set(GRB_IntParam_Threads, 1);			 //< limits the solver to single thread usage

			// --- Solver launch ---
			if (verbose)
				std::cout << "--> Running the solver" << std::endl;
			model.optimize();
			// model.write("model.lp"); //< Writes the model in a file

			// --- Solver results retrieval ---
			if (verbose)
				std::cout << "--> Retrieving solver results " << std::endl;

			int status = model.get(GRB_IntAttr_Status);
			if (status == GRB_OPTIMAL || (status == GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount) > 0))
			{
				if (verbose)
				{
					// the solver has computed the optimal solution or a feasible solution (when the time limit is reached before proving optimality)
					std::cout << "Succes! (Status: " << status << ")" << std::endl; //< prints the solver status (see the gurobi documentation)
					std::cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds" << std::endl;

					std::cout << "--> Printing results " << std::endl;
					// model.write("solution.sol"); //< Writes the solution in a file
					std::cout << "Arc\t Flow/Capacity\n";
					for (size_t i = 0; i < graph.nbEdges; ++i)
					{
						if (f[i].get(GRB_DoubleAttr_X) > 0)
						{
							std::cout << graph.edges[i].startId << "-> " << graph.edges[i].endId << "\t" << f[i].get(GRB_DoubleAttr_X) << "\t" << graph.edges[i].maxCapacity << std::endl;
						}
					}
					std::cout << "Objective value = " << model.get(GRB_DoubleAttr_ObjVal) << "\n"
							  << std::endl; //<gets the value of the objective function for the best computed solution (optimal if no time limit)
				}
				result = model.get(GRB_DoubleAttr_ObjVal);
			}
			else
			{
				// the model is infeasible (maybe wrong) or the solver has reached the time limit without finding a feasible solution
				std::cerr << "Fail! (Status: " << status << ")" << std::endl; //< see status page in the Gurobi documentation
			}
		}
		catch (GRBException e)
		{
			std::cout << "Error code = " << e.getErrorCode() << std::endl;
			std::cout << e.getMessage() << std::endl;
		}
		catch (...)
		{
			std::cout << "Exception during optimization" << std::endl;
		}
		delete[] f;
		return result;
	}

	int minCostFlow(Graph &graph)
	{
		return minCostFlow(graph, false);
	}

	int minCostFlow(Graph &graph, bool verbose)
	{
		GRBVar *f;
		int result = -1;
		try
		{
			if (verbose)
				std::cout << "--> Creating the Gurobi environment" << std::endl;
			GRBEnv env = GRBEnv(true);
			env.start();
			if (verbose)
				std::cout << "--> Creating the Gurobi model" << std::endl;
			GRBModel model = GRBModel(env);
			if (not verbose)
			{
				model.set(GRB_IntParam_OutputFlag, 0);
			}

			if (verbose)
				std::cout << "--> Creating the variables" << std::endl;
			f = new GRBVar[graph.nbEdges];
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				std::stringstream ss;
				ss << "f(" << i << ")";
				f[i] = model.addVar(0.0, INT_MAX, 0.0, GRB_CONTINUOUS, ss.str());
			}

			if (verbose)
				std::cout << "--> Creating the objective function" << std::endl;
			GRBLinExpr obj = 0;
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				obj += f[i] * graph.edges[i].cost;
			}
			model.setObjective(obj, GRB_MINIMIZE);

			if (verbose)
				std::cout << "--> Creating the constraints" << std::endl;
			// flot entrant = flot sortant
			for (size_t i = 0; i < graph.nbVertices; ++i)
			{
				GRBLinExpr lhs = 0;
				lhs += graph.vertices[i].exceedingFlow;
				for (size_t j = 0; j < graph.vertices[i].nbEnteringEdges; ++j)
				{
					lhs += f[graph.vertices[i].enteringEdgesId[j]];
				}
				for (size_t j = 0; j < graph.vertices[i].nbLeavingEdges; ++j)
				{
					lhs -= f[graph.vertices[i].leavingEdgesId[j]];
				}
				std::stringstream ss;
				ss << "Flow(" << i << ")";
				model.addConstr(lhs == 0, ss.str());
			}

			// respect des capacités max
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				GRBLinExpr lhs = f[i] - graph.edges[i].maxCapacity;
				std::stringstream ss;
				ss << "CapacityMax(" << i << ")";
				model.addConstr(lhs <= 0, ss.str());
			}

			// respect des capacités min
			for (size_t i = 0; i < graph.nbEdges; ++i)
			{
				GRBLinExpr lhs = f[i] - graph.edges[i].minCapacity;
				std::stringstream ss;
				ss << "CapacityMin(" << i << ")";
				model.addConstr(lhs >= 0, ss.str());
			}

			// Optimize model
			// --- Solver configuration ---
			if (verbose)
				std::cout << "--> Configuring the solver" << std::endl;
			model.set(GRB_DoubleParam_TimeLimit, 600.0); //< sets the time limit (in seconds)
			model.set(GRB_IntParam_Threads, 1);			 //< limits the solver to single thread usage

			// --- Solver launch ---
			if (verbose)
				std::cout << "--> Running the solver" << std::endl;
			model.optimize();
			// model.write("model.lp"); //< Writes the model in a file

			// --- Solver results retrieval ---
			if (verbose)
				std::cout << "--> Retrieving solver results " << std::endl;

			int status = model.get(GRB_IntAttr_Status);
			if (status == GRB_OPTIMAL || (status == GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount) > 0))
			{
				if (verbose)
				{
					// the solver has computed the optimal solution or a feasible solution (when the time limit is reached before proving optimality)
					std::cout << "Succes! (Status: " << status << ")" << std::endl; //< prints the solver status (see the gurobi documentation)
					std::cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds" << std::endl;

					std::cout << "--> Printing results " << std::endl;
					// model.write("solution.sol"); //< Writes the solution in a file
					std::cout << "Arc - Flow - Capacity - Cost/u\n";
					for (size_t i = 0; i < graph.nbEdges; ++i)
					{
						std::cout << graph.edges[i].startId << "-> " << graph.edges[i].endId << "\t" << f[i].get(GRB_DoubleAttr_X) << "\t" << graph.edges[i].maxCapacity << "\t" << graph.edges[i].cost << std::endl;
					}
					std::cout << "Objective value = " << model.get(GRB_DoubleAttr_ObjVal) << "\n"
							  << std::endl; //<gets the value of the objective function for the best computed solution (optimal if no time limit)
				}
				result = model.get(GRB_DoubleAttr_ObjVal);
			}
			else
			{
				// the model is infeasible (maybe wrong) or the solver has reached the time limit without finding a feasible solution
				std::cerr << "Fail! (Status: " << status << ")" << std::endl; //< see status page in the Gurobi documentation
			}
		}
		catch (GRBException e)
		{
			std::cout << "Error code = " << e.getErrorCode() << std::endl;
			std::cout << e.getMessage() << std::endl;
		}
		catch (...)
		{
			std::cout << "Exception during optimization" << std::endl;
		}
		delete[] f;
		return result;
	}

}
