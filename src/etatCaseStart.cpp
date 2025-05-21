#include "etatCaseStart.h"
#include "etatAttenteStart.h"
#include "RGB.h"
#include "Buzzer.h"
#include "IR.h"
#include "RFID.h"
bool rouge = false;

/**
 * Fonction exécutée pendant l'état d'action
 * Clignottement rapide de la LED
 * passe à l'état FINAL après 5 secondes
 * @param aucun
 * @return aucun
 */

void EtatCaseStart () 
{
    Serial.println(RGB());
    Serial.println("EtatCaseStart");
    //jouerMelodie();
    if (RGB() == 'r') 
    {
        
        //utilisation du capetur NFC
        //décodage matrice
        rfidddd();
        for (int i = 0; i < 169; i++)
        {
            Serial.print(pointdata[i]);
        }
        if(test)
        {
            int** nodes = (int**)malloc(36*sizeof(int*));
            int** matriceDecode = processMatrix(pointdata);
            
            nodes = matrixToNodes(matriceDecode);
            
            int startNode[7] = {0, 0, 0, 0, 0, 0, 0}; // Initialiser avec des valeurs par défaut
            int goalNode[7] =  {0, 0, 0, 0, 0, 0, 0};  // Initialiser avec des valeurs par défaut
            int shortNode[7] =  {0, 0, 0, 0, 0, 0, 0};  // Initialiser avec des valeurs par défaut
            int chillNode[7] =  {0, 0, 0, 0, 0, 0, 0};  // Initialiser avec des valeurs par défaut
            for (int j = 0; j < 36; j++) 
            {

                if (nodes[j][3] == 1) { // Noeud de départ

                    startNode[0] = nodes[j][0];
                    startNode[1] = nodes[j][1];
                    startNode[2] = nodes[j][2];
                    startNode[3] = nodes[j][3];
                    startNode[4] = nodes[j][4];
                    startNode[5] = nodes[j][5];
                    startNode[6] = nodes[j][6];
                }
                if (nodes[j][3] == 2) { // Noeud d'arrivée

                    goalNode[0] = nodes[j][0];
                    goalNode[1] = nodes[j][1];
                    goalNode[2] = nodes[j][2];
                    goalNode[3] = nodes[j][3];
                    goalNode[4] = nodes[j][4];
                    goalNode[5] = nodes[j][5];
                    goalNode[6] = nodes[j][6];
                }
                if (nodes[j][3] == 4) { // Noeud fauteil

                    chillNode[0] = nodes[j][0];
                    chillNode[1] = nodes[j][1];
                    chillNode[2] = nodes[j][2];
                    chillNode[3] = nodes[j][3];
                    chillNode[4] = nodes[j][4];
                    chillNode[5] = nodes[j][5];
                    chillNode[6] = nodes[j][6];
                }
                if (nodes[j][3] == 3) { // Noeud raccourci

                    shortNode[0] = nodes[j][0];
                    shortNode[1] = nodes[j][1];
                    shortNode[2] = nodes[j][2];
                    shortNode[3] = nodes[j][3];
                    shortNode[4] = nodes[j][4];
                    shortNode[5] = nodes[j][5];
                    shortNode[6] = nodes[j][6];
                }

            }

            int* dijkstraphStart = dijkstra(nodes, startNode);
            int* dijkstraphShort = dijkstra(nodes, shortNode);
            int* dijkstraphChill = dijkstra(nodes, chillNode);

            pathdijkStartToShort = antecedant(dijkstraphStart,shortNode,startNode);
            pathdijkStartToChill = antecedant(dijkstraphStart,chillNode,startNode);
            pathdijkShortToChill = antecedant(dijkstraphShort,chillNode,shortNode);
            pathdijkChillToShort = antecedant(dijkstraphChill,shortNode,chillNode);
            pathdijkChillToGoal = antecedant(dijkstraphChill,goalNode,chillNode);
            pathdijkShortToGoal = antecedant(dijkstraphShort,goalNode,shortNode);
            
            instructionStartToShort = seqInstruct2(pathdijkStartToShort,startNode);
            instructionStartToChill = seqInstruct2(pathdijkStartToChill,startNode);
            instructionShortToChill = seqInstruct2(pathdijkShortToChill,shortNode);
            instructionChillToShort = seqInstruct2(pathdijkChillToShort,chillNode);
            instructionChillToGoal = seqInstruct2(pathdijkChillToGoal,chillNode);
            instructionShortToGoal = seqInstruct2(pathdijkShortToGoal,shortNode);

            // for (int i =0 ;i <50;i++)
            // {
            // Serial.print(instruction1[i]);
            // }
            // if(isNodeInPath(pathdijk1, shortNode)){
            // Serial.println("");
            // Serial.print("Shortcut in Path");
            // }
            // else{
            // Serial.println("");
            // Serial.print("Shortcut not in Path");
            // }

            // free(dijkstraph);
            // free(pointdata);
            // free(nodes);
            // free(matriceDecode);
            // free(instruction1);
            rouge = true;
        } 
        else
        {
            Serial.println("Pas de matrice");
        }
    } 
    else if (RGB() == 'g') 
    {
        rouge = false;
        //jouerMelodie();
    }

}

    



bool Transition_CaseStart_AttenteStart () 
{

    //donnée dans la fonction labyrinthe
    return rouge;

}

bool Transition_CaseStart_Recovery () 
{ 

     //"recovery" sur télécommande IR
}