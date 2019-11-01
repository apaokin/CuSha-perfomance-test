#include <string>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "parse_graph.hpp"
#include "user_specified_pre_and_post_processing_functions.hpp"

uint parse_graph::parse(
		std::ifstream& inFile,
		std::vector<initial_vertex>& initGraph,
		const long long arbparam,
		const bool nondirected ) {

	const bool firstColumnSourceIndex = true;

	std::string line;
	char delim[3] = " \t";	//In most benchmarks, the delimiter is usually the space character or the tab character.
	char* pch;
	uint nEdges = 0;

	unsigned int Additionalargc=0;
	char* Additionalargv[ 61 ];

	// Read the input graph line-by-line.
	int vertices_count;
	long long edges_count;
	inFile.read((char*)(&vertices_count), sizeof(int));
  inFile.read((char*)(&edges_count), sizeof(long long));
	initGraph.resize(vertices_count);
	for(long long i = 0; i < edges_count; i++){
		// int firstIndexInt, secondIndexInt;

		uint firstIndex, secondIndex;
		inFile.read((char*)(&firstIndex), sizeof(int));
		inFile.read((char*)(&secondIndex), sizeof(int));
		inFile.read((char*)(&initGraph.at(firstIndex).VertexValueStatic.NbrsNum), sizeof(int));
		// std::cout << firstIndex << ' ' << secondIndex << ' ' << initGraph.at(firstIndex).VertexValueStatic.NbrsNum<<'\n';

		// inFile.read((char*)(&secondIndex), sizeof(int));
		// inFile.read((char*)(&firstIndex), sizeof(int));
		// inFile.read((char*)(&initGraph.at(firstIndex).VertexValueStatic.NbrsNum), sizeof(int));

		// inFile.read((char*)(&initGraph.at(firstIndex).VertexValueStatic.NbrsNum), sizeof(int));
		neighbor nbrToAdd;
		nbrToAdd.srcIndex = firstIndex;
		initGraph.at(secondIndex).nbrs.push_back( nbrToAdd );

		// initGraph.at(srcVertexIndex).VertexValueStatic
	  // file.read((char*)(&edges_count), sizeof(long long));
		// {
		// 	neighbor nbrToAdd;
		// 	nbrToAdd.srcIndex = srcVertexIndex;
		//
		// 	Additionalargc=0;
		// 	Additionalargv[ Additionalargc ] = strtok( NULL, delim );
		// 	while( Additionalargv[ Additionalargc ] != NULL ){
		// 		Additionalargc++;
		// 		Additionalargv[ Additionalargc ] = strtok( NULL, delim );
		// 	}
		// 	completeEntry(	Additionalargc,
		// 				Additionalargv,
		// 				srcVertexIndex,
		// 				dstVertexIndex,
		// 				&(nbrToAdd.edgeValue),
		// 				(initGraph.at(srcVertexIndex).vertexValue),
		// 				&(initGraph.at(srcVertexIndex).VertexValueStatic),
		// 				(initGraph.at(dstVertexIndex).vertexValue),
		// 				&(initGraph.at(dstVertexIndex).VertexValueStatic),
		// 				arbparam );
		//
		// 	initGraph.at(dstVertexIndex).nbrs.push_back( nbrToAdd );
		// 	nEdges++;
		// }
	}

	return edges_count;

	while( std::getline( inFile, line ) ) {
		if( line[0] < '0' || line[0] > '9' )	// Skipping any line blank or starting with a character rather than a number.
			continue;
		char cstrLine[256];
		std::strcpy( cstrLine, line.c_str() );
		uint firstIndex, secondIndex;

		pch = strtok(cstrLine, delim);
		if( pch != NULL )
			firstIndex = atoi( pch );
		else
			continue;
		pch = strtok( NULL, delim );
		if( pch != NULL )
			secondIndex = atoi( pch );
		else
			continue;

		uint theMax = std::max( firstIndex, secondIndex );
		uint srcVertexIndex = firstColumnSourceIndex ? firstIndex : secondIndex;
		uint dstVertexIndex = firstColumnSourceIndex ? secondIndex : firstIndex;
		if( initGraph.size() <= theMax )
			initGraph.resize(theMax+1);
		{
			neighbor nbrToAdd;
			nbrToAdd.srcIndex = srcVertexIndex;

			Additionalargc=0;
			Additionalargv[ Additionalargc ] = strtok( NULL, delim );
			while( Additionalargv[ Additionalargc ] != NULL ){
				Additionalargc++;
				Additionalargv[ Additionalargc ] = strtok( NULL, delim );
			}
			completeEntry(	Additionalargc,
						Additionalargv,
						srcVertexIndex,
						dstVertexIndex,
						&(nbrToAdd.edgeValue),
						(initGraph.at(srcVertexIndex).vertexValue),
						&(initGraph.at(srcVertexIndex).VertexValueStatic),
						(initGraph.at(dstVertexIndex).vertexValue),
						&(initGraph.at(dstVertexIndex).VertexValueStatic),
						arbparam );

			initGraph.at(dstVertexIndex).nbrs.push_back( nbrToAdd );
			nEdges++;
		}
		// if( nondirected ) {
		//
		// 	uint tmp = srcVertexIndex;
		// 	srcVertexIndex = dstVertexIndex;
		// 	dstVertexIndex = tmp;
		//
		// 	neighbor nbrToAdd;
		// 	nbrToAdd.srcIndex = srcVertexIndex;
		//
		// 	Additionalargc=0;
		// 	Additionalargv[ Additionalargc ] = strtok( NULL, delim );
		// 	while( Additionalargv[ Additionalargc ] != NULL ){
		// 		Additionalargc++;
		// 		Additionalargv[ Additionalargc ] = strtok( NULL, delim );
		// 	}
		// 	completeEntry(	Additionalargc,
		// 				Additionalargv,
		// 				srcVertexIndex,
		// 				dstVertexIndex,
		// 				&(nbrToAdd.edgeValue),
		// 				(initGraph.at(srcVertexIndex).vertexValue),
		// 				&(initGraph.at(srcVertexIndex).VertexValueStatic),
		// 				(initGraph.at(dstVertexIndex).vertexValue),
		// 				&(initGraph.at(dstVertexIndex).VertexValueStatic),
		// 				arbparam );
		//
		// 	initGraph.at(dstVertexIndex).nbrs.push_back( nbrToAdd );
		// 	nEdges++;
		// }
	}

	return nEdges;

}
