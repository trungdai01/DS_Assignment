#include "./bellman.h"

int getIntVertex(char vertex)
{
    return vertex >= 'a' ? vertex - 'a' : vertex - 'A';
}

char getCharVertex(int vertex)
{
    return vertex + 'A';
}

void copyBFValueToBFValuePrev(int BFValue[20], int BFValuePrev[20])
{
    for (int i = 0; i < 20; i++)
    {
        BFValuePrev[i] = BFValue[i];
    }
}

void BF(int G[20][20], int numOfVertices, char start_vertex, int BFValue[20], int BFPrev[20])
{
    int BFValuePrev[20];
    BFValue[getIntVertex(start_vertex)] = 0;
    copyBFValueToBFValuePrev(BFValue, BFValuePrev);

    for (int src = 0; src < numOfVertices; src++)
    {
        for (int dest = 0; dest < numOfVertices; dest++)
        {
            if (G[src][dest] != 0 && BFValuePrev[src] != -1)
            {
                if (BFValuePrev[dest] == -1 && BFPrev[dest] == -1)
                {
                    BFValue[dest] = BFValuePrev[src] + G[src][dest];
                    BFPrev[dest] = src;
                }
                else if (BFValuePrev[src] + G[src][dest] < BFValue[dest])
                {
                    BFValue[dest] = BFValuePrev[src] + G[src][dest];
                    BFPrev[dest] = src;
                }
            }
        }
    }
}

string BF_Path(int G[20][20], int numOfVertices, char start_vertex, char dest_vertex)
{
    int BFValue[20];
    int BFPrev[20];

    for (int i = 0; i < 20; i++)
    {
        BFPrev[i] = -1;
        BFValue[i] = -1;
    }

    for (int i = 0; i < numOfVertices; i++)
    {
        BF(G, numOfVertices, start_vertex, BFValue, BFPrev);
    }

    int src = getIntVertex(start_vertex), dest = getIntVertex(dest_vertex);
    string BFPath = "";
    BFPath += dest_vertex;

    while (src != dest)
    {
        BFPath += " ";
        BFPath += getCharVertex(BFPrev[dest]);
        dest = BFPrev[dest];
    }

    reverse(BFPath.begin(), BFPath.end());

    return BFPath;
}