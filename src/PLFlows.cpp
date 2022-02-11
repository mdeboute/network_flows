#include "PLFlows.hpp"
#include "Graph.hpp"
#include "gurobi_c++.h"
#include<string>
#include<sstream>
#include<iostream>
#include <cstdint>
#include <climits>
using namespace std;

namespace PL
{
  void maxFlow(Graph &graph, int begin, int end)
  {
    const int nbEdges = graph.nbEdges;

    GRBVar* f;
    try{
  		cout<<"--> Creating the Gurobi environment"<<endl;
  		GRBEnv env = GRBEnv(true);
  		env.start();
  		cout<<"--> Creating the Gurobi model"<<endl;
  		GRBModel model = GRBModel(env);

  		cout<<"--> Creating the variables"<<endl;
  		f = new GRBVar[nbEdges];
  		for(size_t i=0;i<nbEdges;++i){
  			stringstream ss;
  			ss << "f(" << i<<")";
  			f[i]=model.addVar(0.0, INT_MAX, 0.0, GRB_CONTINUOUS, ss.str());
  		}

      cout<<"--> Creating the objective function"<<endl;
  		GRBLinExpr obj = 0;
  		for(size_t i=0;i<graph.vertices[begin].nbEnteringEdges;++i){
  			obj+=f[graph.vertices[begin].enteringEdgesId[i]];
  		}
      for(size_t i=0;i<graph.vertices[begin].nbLeavingEdges;++i){
  			obj-=f[graph.vertices[begin].leavingEdgesId[i]];
  		}
  		model.setObjective(obj, GRB_MINIMIZE);

      cout<<"--> Creating the constraints"<<endl; //Erreur de segmentation
      // flot entrant = flot sortant
      for(size_t i=0;i<nbEdges;++i){
        if(i!=begin && i!=end){
          GRBLinExpr lhs = 0;
          for(size_t j=0;j<graph.vertices[i].nbEnteringEdges;++j){
      			lhs+=f[graph.vertices[i].enteringEdgesId[j]];
      		}
          for(size_t j=0;j<graph.vertices[i].nbLeavingEdges;++j){
      			lhs-=f[graph.vertices[i].leavingEdgesId[j]];
      		}
    			stringstream ss;
    			ss << "Capacity("<<i<<")";
    			model.addConstr(lhs==0,ss.str());
        }
  		}

  		// respect des capacités
  		for(size_t i=0;i<nbEdges;++i){
  			GRBLinExpr lhs = f[i] - graph.edges[i].maxCapacity;
  			stringstream ss;
  			ss << "Capacity("<<i<<")";
  			model.addConstr(lhs<=0,ss.str());
  		}

      // Optimize model
  		// --- Solver configuration ---
  		cout<<"--> Configuring the solver"<<endl;
  		model.set(GRB_DoubleParam_TimeLimit, 600.0); //< sets the time limit (in seconds)
  		model.set(GRB_IntParam_Threads,1); //< limits the solver to single thread usage


  		// --- Solver launch ---
  		cout<<"--> Running the solver"<<endl;
  		model.optimize();
  		//model.write("model.lp"); //< Writes the model in a file

  		// --- Solver results retrieval ---
  		cout<<"--> Retrieving solver results "<<endl;

  		int status = model.get(GRB_IntAttr_Status);
  		if (status == GRB_OPTIMAL || (status== GRB_TIME_LIMIT && model.get(GRB_IntAttr_SolCount)>0))
  		{
  			//the solver has computed the optimal solution or a feasible solution (when the time limit is reached before proving optimality)
  			cout << "Succes! (Status: " << status << ")" << endl; //< prints the solver status (see the gurobi documentation)
  			cout << "Runtime : " << model.get(GRB_DoubleAttr_Runtime) << " seconds"<<endl;

  			cout<<"--> Printing results "<<endl;
  			//model.write("solution.sol"); //< Writes the solution in a file
  			cout << "Objective value = "<< model.get(GRB_DoubleAttr_ObjVal)  << endl; //<gets the value of the objective function for the best computed solution (optimal if no time limit)
  			for(size_t i=0;i<nbEdges;++i){
  				cout << "- Flow "<<i<<" is "<<f[i].get(GRB_DoubleAttr_X)<< endl;
  			}

  		} else
  		{
  			// the model is infeasible (maybe wrong) or the solver has reached the time limit without finding a feasible solution
  			cerr << "Fail! (Status: " << status << ")" << endl; //< see status page in the Gurobi documentation
  		}
  	} catch(GRBException e) {
  		cout << "Error code = " << e.getErrorCode() << endl;
  		cout << e.getMessage() << endl;
  	} catch(...) {
  		cout << "Exception during optimization" << endl;
  	}
  	delete[] f;
  }


  void minCostFlow(Graph &graph)
  {

  }

}
