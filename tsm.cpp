#include "tsm.h"

int TravelPath(int G[][20], int startVertex, vector<int>& path, int numOfVertices)
{
    const int totalCases = 1 << numOfVertices;
    int** table = new int*[totalCases];
    int** TSPPrev = new int*[totalCases];
    for (int i = 0; i < totalCases; i++)
    {
        table[i] = new int[numOfVertices];
        TSPPrev[i] = new int[numOfVertices];
    }

    for (int i = 0; i < totalCases; i++)
    {
        for (int j = 0; j < numOfVertices; j++)
        {
            table[i][j] = INT16_MAX;
            TSPPrev[i][j] = -1;
        }
    }

    int startCase = 1 << startVertex;
    table[startCase][startVertex] = 0;

    for (int caseNum = 1; caseNum < totalCases; caseNum++)
    {
        for (int src = 0; src < numOfVertices; src++)
        {
            bool isCityIncluded = caseNum & (1 << src);

            if (!isCityIncluded) continue;

            for (int dst = 0; dst < numOfVertices; ++dst)
            {
                bool isCityOverlapped = caseNum & (1 << dst);

                if (src == dst || isCityOverlapped) continue;

                int newDistance = table[caseNum][src] + G[src][dst];

                int caseIncludeSrcDst = caseNum | (1 << dst);

                if (G[src][dst] != 0 && (newDistance < table[caseIncludeSrcDst][dst]))
                {
                    table[caseIncludeSrcDst][dst] = newDistance;
                    TSPPrev[caseIncludeSrcDst][dst] = src;
                }
            }
        }
    }

    int lastCase = totalCases - 1;
    int lastVertex = -1;
    int minimumPath = INT_MAX;
    for (int src = 0; src < numOfVertices; ++src)
    {
        int newPath = table[lastCase][src] + G[src][startVertex];
        if (newPath < minimumPath)
        {
            minimumPath = newPath;
            lastVertex = src;
        }
    }
    path.push_back(lastVertex);
    while (lastCase != startCase)
    {
        int nextVertex = TSPPrev[lastCase][lastVertex];
        path.push_back(nextVertex);
        lastCase ^= (1 << lastVertex);
        lastVertex = nextVertex;
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < totalCases; i++)
    {
        delete[] table[i];
        delete[] TSPPrev[i];
    }
    delete[] table;
    delete[] TSPPrev;

    return minimumPath;
}

string Traveling(int G[][20], int numOfVertices, char start)
{
    vector<int> path;
    int shortestPath = TravelPath(G, start - 'A', path, numOfVertices);
    string travelPath;
    for (int vertex : path)
    {
        travelPath += getCharVertex(vertex);
        travelPath += " ";
    }
    if (numOfVertices > 0) travelPath += start;
    return travelPath;
}