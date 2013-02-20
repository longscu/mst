#include "directedGraph.h"


unsigned int DirectedGraph::getNoVertices()
{
	return noVertices;
}
void DirectedGraph::setNoVertices(unsigned int numV)
{
	noVertices = numV;
}

unsigned int DirectedGraph::getNoEdges()
{
	return noEdges;
}
void DirectedGraph::setNoEdges(unsigned int numE)
{
	noEdges = numE;
}


void DirectedGraph::createGraph(Graph &g)
{

	
	Graph::edgeItr minItr;
	Graph::vertexItr vItr;
	
	DirectedEdge *e;
		
	//g.printGraph();
	
	dirEdgeList.clear();

	STXXL_MSG("Check");
	
	for(vItr = g.getFirstVertex(); !(g.checkVertexListEnd(vItr)); vItr++)
	{
		//STXXL_MSG("Check Inside for");
		if(!(g.checkEdgeListEnd(vItr->second)) && vItr->second->getEdgeWt() <= (vItr->first).getBlockingValue())
		{
			//STXXL_MSG("Check inside if");
			minItr=vItr->second;
			e = new DirectedEdge(minItr->getDst(),minItr->getSrc(),minItr->getEdgeWt());
			dirEdgeList.push_back(*e);
		}
	}

	noEdges=dirEdgeList.size();	

	stxxl::sort(dirEdgeList.begin(),dirEdgeList.end(),dirCmpEdge(),INTERNAL_MEMORY_FOR_SORTING);
	STXXL_MSG("Directed graph created");
	//printGraph();
	
}

void DirectedGraph::detectCycle()
{
		//dirVertexItr vItr;
		dirEdgeItr eItr,NewEnd;
		dirEdgeType cycleEdges;
			
		stxxl::sort(dirEdgeList.begin(),dirEdgeList.end(),dirCmpWt(),INTERNAL_MEMORY_FOR_SORTING);
		roots.clear();
		cycleEdges.clear();

		for(eItr=dirEdgeList.begin();eItr!=dirEdgeList.end();eItr++)
		{

			if((eItr+1)!=dirEdgeList.end() && eItr->equals(*(eItr+1)))
			{
				cycleEdges.push_back(*(eItr+1));	
				roots.push_back(*eItr);
				eItr++;					
			}
		}
		
		//STXXL_MSG("Detect");	
		
		stxxl::sort(dirEdgeList.begin(),dirEdgeList.end(),dirCmpEdge(),INTERNAL_MEMORY_FOR_SORTING);	
		
		if(!cycleEdges.empty())
		{
			for(eItr=cycleEdges.begin();eItr!=cycleEdges.end();eItr++)
			{
				NewEnd = std::remove(dirEdgeList.begin(),dirEdgeList.end(),*eItr);
				dirEdgeList.resize(NewEnd - dirEdgeList.begin());
			}
		}
	
		//STXXL_MSG("Detect");
		/*vertexType result;
		Vertex *v;
		dirVertexList.clear();
		for(eItr=dirEdgeList.begin();eItr!=dirEdgeList.end();)
		{
			if(eItr!=dirEdgeList.end())
			{
				v = new Vertex(eItr->getSrc());
				result.first = *v;
				result.second= eItr;
				dirVertexList.push_back(result);
			}
			while(eItr!=dirEdgeList.end()&&eItr->getSrc()==v->getVertexId())
			{
				eItr++;
			}
			
			//STXXL_MSG("Vertex:"<<(result.first).vertex_id<<" "<<(result.second)->src);
			
		}
		*/	
		
		noEdges=dirEdgeList.size();
		//noVertices = dirVertexList.size();
		STXXL_MSG("No of vertices: "<<noVertices);
		STXXL_MSG("Number of edges: "<<noEdges<<std::endl);
		STXXL_MSG("Cycle detected");
		//printGraph();
		
}

void DirectedGraph::copyEdgeList(dirEdgeType &list)
{
	list = dirEdgeList;
}

DirectedGraph::dirEdgeItr DirectedGraph::getFirstRoot()
{
	return roots.begin();
}
DirectedGraph::dirEdgeItr DirectedGraph::getFirstEdge()
{
	return dirEdgeList.begin();
}
DirectedGraph::dirEdgeItr DirectedGraph::getEdgeListEnd()
{
	return dirEdgeList.end();
}

DirectedGraph::dirEdgeItr DirectedGraph::getRootEnd()
{
	return roots.end();
}

bool DirectedGraph::isRoot(unsigned int src,unsigned int dst,unsigned int wt)
{
	DirectedEdge *e;
	e = new DirectedEdge(src,dst,wt);	
	
	dirEdgeItr temp = stxxl::find(roots.begin(),roots.end(),*e, 4);

	return (temp!=roots.end());

}



void DirectedGraph::printGraph()
{
	dirEdgeItr itr;
	
	STXXL_MSG("**Directed Graph -  Edge Listing **"<<std::endl);
	STXXL_MSG("No of vertices: "<<noVertices);
	STXXL_MSG("Number of edges: "<<noEdges<<std::endl);
	
	for(itr=dirEdgeList.begin();itr!=dirEdgeList.end();itr++)
	{
		STXXL_MSG(" (" <<(itr->getSrc())<<", " <<(itr->getDst())<<", "<<(itr->getEdgeWt())<<") ");
	}
	STXXL_MSG("\n**Directed Graph Components -  Roots Listing **");
	for(itr=roots.begin();itr!=roots.end();itr++)
	{
		STXXL_MSG(" (" <<(itr->getSrc())<<", " <<(itr->getDst())<<", "<<(itr->getEdgeWt())<<") ");
	}
	
}

/*
int main()
{
	unsigned int num_v,num_e;
	
	STXXL_MSG("Graph\n");
	STXXL_MSG("Num vertices");
	std::cin>>num_v;
	STXXL_MSG("Edges :");
	std::cin>>num_e;
	
	Graph g(num_v,num_e);
	g.generateGraph();
	g.printGraph();

	
	stxxl::stats_data stats_begin(*stxxl::stats::get_instance());

    	stxxl::timer Timer;
	Timer.start();
	DirectedGraph dag(num_v,num_e);
	dag.createGraph(g);	
	dag.detectCycle();
	
	

	STXXL_MSG("Directed Graph creation elapsed time: " << (Timer.mseconds() / 1000.) <<
              " seconds : " << (double(num_e) / (Timer.mseconds() / 1000.)) << " edges per sec");

    	std::cout << stxxl::stats_data(*stxxl::stats::get_instance()) - stats_begin;
	dag.printGraph();
	return 0;
}
	
*/



		
		

	
		
	
	
