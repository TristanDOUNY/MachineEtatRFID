///////////////////////////////////////////////////////////////////////////////////////////////////////////
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
//-- Co-programme réalisée en colaboration avec DOUNY Tristan (équipe H) et GILLIEAUX Alexis (équipe I)--//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
///////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "RFID.h"


/**
 * Fonction exécutée pendant l'état initial
 * éteint la LED et passe à l'état ATTENTE sur appui du bouton
 * @param aucun
 * @return code_matrice
 */

MFRC522 mfrc522(SS_PIN, RST_PIN);
// Clé par défaut (valeurs d’usine)
MFRC522::MIFARE_Key key;

void rfid_init() {
    SPI.begin(); // Initialisation du bus SPI
    mfrc522.PCD_Init(); //
    Serial.println("Scan PICC to see UID and type...");

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
      }
} 

bool flagfin;
bool test = false;
//int* pointdata = (int*)malloc(169*sizeof(int));
//Fonction de base
void rfidddd() 
{

  // Attente d’une carte RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
  }
  // Récupération des informations de la carte RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;
  }
  int tampon[169];
  int labyrinthe[13][13];

  
  //   Read bloc 0 1 2
  //   write data
  Serial.print(rfid1Block(4));
  Serial.print(rfid1Block(5));
  Serial.print(rfid1Block(6));
  Serial.print(rfid1Block(8));
  Serial.print(rfid1Block(9));
  Serial.print(rfid1Block(10));
  Serial.print(rfid1Block(12));
  Serial.print(rfid1Block(13));
  Serial.print(rfid1Block(14));
  Serial.print(rfid1Block(16));
  Serial.print(rfid1Block(17));
  // Affichage des informations de la carte RFID.
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  test = true;
  // pointdata = data
}


int j=0;
int data[169];


bool rfid1Block(byte block ) {
  
  bool flagnfc = false;

  
    byte buf[18];
    byte size = 18;
    int secteur = block/4;
    byte firstBlock = secteur*4 +3;
    //Serial.println(firstBlock);
    MFRC522::StatusCode status = mfrc522.PCD_Authenticate(
      MFRC522::PICC_CMD_MF_AUTH_KEY_A,
      firstBlock,
      &key,
      &(mfrc522.uid)
    );
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      //Serial.println(GetStatusCodeName(status));
      return true;
    }
		// Read block
		byte byteCount = sizeof(buf);
    status = mfrc522.MIFARE_Read(block, buf, &size);


    // 📖 Lecture du bloc4
  

  if (status != MFRC522::STATUS_OK) {
    Serial.print("Erreur lecture bloc ");
    Serial.print(block);
    Serial.print(" : ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    // mfrc522.PICC_HaltA();
    // mfrc522.PCD_StopCrypto1();
    return false;
  } else {
    //Serial.print(j);
    Serial.print("Bloc ");
    Serial.print(block);
    Serial.println(" :");
    for (int i = 0; i < 16; i++) {
      
      Serial.print(buf[i]);
      Serial.print(" ");
      pointdata[j]=buf[i];

      j++;
      
      if(j > 166)
      {
        flagnfc = 1;
      }

    }
    Serial.println();
  }

  //impression du tableau data
  int hex = 7;
  if(flagnfc == 1)
  {
  Serial.println("--------------tableau data------------");
  
  for (int k=0;k<169;k++)
  {

    if (k == hex)
    {
      Serial.print(data[k]);
      Serial.print(" ");
      Serial.println();
      hex += 8;
      switch (k)
      

      {
      case 7:
        Serial.println("11111111");
        Serial.println(" -- ");
        break;
      case 15:
        Serial.print("11111112");
        Serial.println(" -- ");
        break;
      case 23:
        Serial.print("01004100");
        Serial.println(" -- ");
        break;
      case 31:
        Serial.print("01111010");
        Serial.println(" -- ");
        break;
      case 39:
        Serial.print("11101011");
        Serial.println(" -- ");
        break;
      case 47:
        Serial.print("01010000");
        Serial.println(" -- ");
        break;
      case 55:
        Serial.print("01011010");
        Serial.println(" -- ");
        break;
      case 63:
        Serial.print("11111110");
        Serial.println(" -- ");
        break;
      case 71:
        Serial.print("11010000");
        Serial.println(" -- ");
        break;
      case 79:
        Serial.print("00000110");
        Serial.println(" -- ");
        break;
      case 87:
        Serial.print("11111111");
        Serial.println(" -- ");
        break;
      case 95:
        Serial.print("10110000");
        Serial.println(" -- ");
        break;
      case 103:
        Serial.print("00010031");
        Serial.println(" -- ");
        break;
      case 111:
        Serial.print("10101111");
        Serial.println(" -- ");
        break;
      case 119:
        Serial.print("10131101");
        Serial.println(" -- ");
        break;
      case 127:
        Serial.print("01000001");
        Serial.println(" -- ");
        break;
      case 135:
        Serial.print("21101110");
        Serial.println(" -- ");
        break;
      case 143:
        Serial.print("11111011");
        Serial.println(" -- ");
        break;
      case 151:
        Serial.print("00000000");
        Serial.println(" -- ");
        break;
      case 159:
        Serial.print("00011111");
        Serial.println(" -- ");
        break;
      case 167:
        Serial.print("11111111");
        Serial.println(" -- ");
      }
      
    
    }
    else
    {
      //Serial.println(j);
      Serial.print(data[k]);
      Serial.print(" ");
    }
    
  }
  }
  return true;
}
int* dijkstra(int** nodes, int start[]) {
    Serial.print("test dijkstra");
    int dist[36]; // Tableau pour stocker les distances
    int* prev = (int*)malloc(36 * sizeof(int)); // Tableau pour stocker les noeuds précédents
    int priorityQueue[36]; // File de priorité pour les noeuds à explorer
    dist[start[0]] = 0; // Distance du noeud de départ à lui-même
    priorityQueue[start[0]] = 0; // Ajouter le noeud de départ à la file de priorité
    for (int i = 0; i < 36; i++) {
        if (i != start[0]) {
            dist[i] = 256; // Initialiser les distances à l'infini
            prev[i] = -1; // Initialiser les noeuds précédents à -1
            priorityQueue[i] = 256; // Initialiser la file de priorité
        }
    }

    // for (int j = 0; j < 36; j++){
    //     Serial.print("Noeud ");
    //     Serial.print(nodes[j][0]);
    //     Serial.print(" : ");
    //     Serial.print(nodes[j][1]);
    //     Serial.print(" ");
    //     Serial.print(nodes[j][2]);
    //     Serial.print(" ");
    //     Serial.print(nodes[j][3]);
    //     Serial.print(" ");
    //     Serial.print(nodes[j][4]);
    //     Serial.print(" ");
    //     Serial.print(nodes[j][5]);
    //     Serial.print(" ");
    //     Serial.print(nodes[j][6]);
    //     Serial.print(" ");
    //     Serial.println(nodes[j][7]);
    //   }
    while (true){
        // Serial.print("rentrée dans la boucle");
        int isPriorityQueueEmpty = 1;
        for (int i = 0; i < 36; i++){
            if (priorityQueue[i] != 256){
                isPriorityQueueEmpty = 0;
                break;
            }
        }

        
        if (isPriorityQueueEmpty == 1){
            // Serial.print("Prev :");
            // for (int i = 0; i < 36; i++){
            //     Serial.print(prev[i]);
            //     Serial.print(" ");
            // }
            // Serial.println(" ");
            return prev; // Si la file de priorité est vide, sortir de la boucle
        }
        else{
            int currentNode = -1;
            int minDistance = 256;
            for (int i = 0; i < 36; i++)
            {
                if (priorityQueue[i] != 256 && dist[i] < minDistance) {
                    minDistance = dist[i];
                    currentNode = i;
                    
                }
            }
            // Serial.print("Noeud courant : ");
            // Serial.println(currentNode);
            // Serial.print("PriorityQueue : ");
            // for (int i = 0; i < 36; i++){
            //     Serial.print(priorityQueue[i]);
            //     Serial.print(" ");
            // }
            // Serial.println(" ");
            priorityQueue[currentNode] = 256; // Marquer le noeud comme visité
            int neighbor1 = currentNode - 1; // Noeud à gauche
            int neighbor2 = currentNode + 1; // Noeud à droite
            int neighbor3 = currentNode - 6; // Noeud en haut
            int neighbor4 = currentNode + 6; // Noeud en bas
            if (neighbor1 < 0 || currentNode % 6 - 1 < 0) // Noeud inaccessible
            {
                neighbor1 = -1;
            }
            if (neighbor2 > 35 || currentNode % 6 + 1 > 5) // Noeud inaccessible
            {
                neighbor2 = -1;
            }
            if (neighbor3 < 0)
            {
                neighbor3 = -1;
            }
            if (neighbor4 > 35)
            {
                neighbor4 = -1;
            }
            if (neighbor1 != -1) {
                if (nodes[neighbor1][5] == 1){
                    neighbor1 = -1; // Noeud inaccessible
                }
            }
            if (neighbor2 != -1) {
                if (nodes[neighbor2][4] == 1){
                    neighbor2 = -1; // Noeud inaccessible
                }
            }
            if (neighbor3 != -1) {
                if (nodes[neighbor3][7] == 1){
                    neighbor3 = -1; // Noeud inaccessible
                }
            }
            if (neighbor4 != -1) {
                if (nodes[neighbor4][6] == 1){
                    neighbor4 = -1; // Noeud inaccessible
                }
            }
            int neighbors[4] = { neighbor1, neighbor2, neighbor3, neighbor4 };
            // Serial.print("Noeud courant : ");
            // Serial.print(currentNode);
            // Serial.print(" , Neigbors : ");
            // for (int i = 0; i < 4; i++){
            //     Serial.print(neighbors[i]);
            //     Serial.print(" : ");
            //     Serial.print(nodes[neighbors[i]][4+i]);
            //     Serial.print(" , ");
            // }
            // Serial.println(" ");
            for (int i = 0; i < 4; i++) {
                if (neighbors[i] != -1 ) {
                    int neighborNode = neighbors[i];
                    int alt = dist[currentNode] + 1; // Coût entre les noeuds adjacents est 1
                    if (alt < dist[neighborNode]) {
                        dist[neighborNode] = alt;
                        prev[neighborNode] = currentNode; // Mettre à jour le noeud précédent
                        priorityQueue[neighborNode] = alt; // Ajouter le voisin à la file de priorité
                        // Serial.print("Noeud voisin : ");
                        // Serial.print(neighborNode);
                        // Serial.print(" , Prev : ");
                        // Serial.print(prev[neighborNode]);
                        // Serial.print(" , Noeud courrant : ");
                        // Serial.println(currentNode);
                    }
                }
            }
        }
    }
}
int** processMatrix(int* matriceNonDecode)
{
    int** matriceDecode = (int**)malloc(13 * sizeof(int*));
    if (matriceNonDecode == NULL) {
        return NULL;
    }

    for (int i = 0; i < 13; i++)
    {
        matriceDecode[i] = (int*)malloc(13 * sizeof(int));
        for (int j = 0; j < 13; j++)
        {
            matriceDecode[i][j] = matriceNonDecode[i * 13 + j];
        }
    }
    free(matriceNonDecode); 
    return matriceDecode;
}
int** matrixToNodes(int** matrix){
    Serial.println("Matrice traitée :");
    for (int j = 0; j < 13; j++) {
      for (int k = 0; k < 13; k++) {
        Serial.print(matrix[j][k]);
        Serial.print(" ");
      }
      Serial.println();
    }
int** nodes = (int**)malloc(36*sizeof(int*));
  for (int i = 0; i < 36; i++){
      nodes[i] = (int*)malloc(8*sizeof(int));
      nodes[i][0] = i; // nom du noeud
      nodes[i][1] = i%6; // x coordinate
      nodes[i][2] = i/6; // y coordinate
      nodes[i][3] = matrix[1+2*(i/6)][1+2*(i%6)]; //type
      nodes[i][4] = matrix[1+2*(i/6)][1+2*(i%6)-1]; //left
      nodes[i][5] = matrix[1+2*(i/6)][1+2*(i%6)+1]; //right
      nodes[i][6] = matrix[1+2*(i/6)-1][1+2*(i%6)]; //up
      nodes[i][7] = matrix[1+2*(i/6)+1][1+2*(i%6)]; //down
    }
    for (int i = 0; i < 36; i++){
      // Serial.print("Noeud ");
      // Serial.print(i);
      // Serial.print(" : ");
      // Serial.print(i);
      // Serial.print("//");
      // Serial.println(i%7);
      // Serial.print(" ");
      // Serial.print(i/6);
      // Serial.print(" ");
      // Serial.print(matrix[1+2*(i/6)][1+2*(i%6)]);
      // Serial.print(" ");
      // Serial.print(matrix[1+2*(i/6)][1+2*(i%6)-1]);
      // Serial.print(" ");
      // Serial.print(matrix[1+2*(i/6)][1+2*(i%6)+1]);
      // Serial.print(" ");
      // Serial.print(matrix[1+2*(i/6)-1][1+2*(i%6)]);
      // Serial.print(" ");
      // Serial.println(matrix[1+2*(i/6)+1][1+2*(i%6)]);
    }
    // for (int j = 0; j < 36; j++){
    //   Serial.print("Noeud ");
    //   Serial.print(nodes[j][0]);
    //   Serial.print(" : ");
    //   Serial.print(nodes[j][1]);
    //   Serial.print(" ");
    //   Serial.print(nodes[j][2]);
    //   Serial.print(" ");
    //   Serial.print(nodes[j][3]);
    //   Serial.print(" ");
    //   Serial.print(nodes[j][4]);
    //   Serial.print(" ");
    //   Serial.print(nodes[j][5]);
    //   Serial.print(" ");
    //   Serial.print(nodes[j][6]);
    //   Serial.print(" ");
    //   Serial.println(nodes[j][7]);
    // }
  return nodes;
}

int* path (int* prev,int goal[], int start[]){
    int reversedPath[36];
    int pathSize = 0;
    for (int i = 0; i < 36; i++)
    {
        reversedPath[i] = -1; // Initialiser le tableau de chemin inversé
    }
    reversedPath[0]= prev[goal[0]]; // Marquer le noeud de but comme visité
    for (int i = 1; i < 36; i++){
        if(reversedPath[i] == -1 || reversedPath[i] == start[0]){
            break;
        }
        reversedPath[i] = prev[reversedPath[i-1]]; // Marquer le noeud de but comme visité
        pathSize++;
    }
    int* path = (int*)malloc((pathSize + 1) * sizeof(int)); // Allouer de la mémoire pour le chemin
    for (int i = 0; i < pathSize; i++){
        path[i] = reversedPath[pathSize - i - 1]; // Inverser le chemin
    } 
    free(prev); // Libérer la mémoire allouée pour le tableau de noeuds précédents  
    return path; // Retourner le chemin
}
int* antecedant(int* prev, int goal[], int start[]) {
    int* revpath = (int*)malloc(36 * sizeof(int));

    for (int i = 0; i < 36; i++) {
        revpath[i] = -1;
    }

    int j = 0;
    Serial.print("Noeud de but : ");
    Serial.println(goal[0]);
    int current = goal[0];
    Serial.print("Noeud courant : ");
    Serial.println(current);
    revpath[0] = current;
    j++;
    // On remonte jusqu'à start[0], ou tant que prev est valide
    while (revpath[j - 1] != start[0]) {
        current = prev[revpath[j - 1]];
        revpath[j++] = current;
    }

    return revpath;
}

char deterDir(int startNode[])
{

  if(startNode[4] == 2)
  {
    Serial.println("Oeust");
    return 'G'; //direction ouest
  }
  
  if(startNode[5] == 2)
  {
    Serial.println("Est");
    return 'D'; //direction est
  }

  if(startNode[6] == 2)
  {
    Serial.println("Nord");
    return 'H'; //direction nord
  }

  if(startNode[7] == 2)
  {
    Serial.println("Sud");
    return 'B'; //direction sud
  }


}

int indicePath(int* pathdijk1)
{
  for (int i = 0; i < 36; i++)
  {
    if(pathdijk1[i] == -1)
    {
      return i-1;
    }
  }
  
}

int* seqInstruct2(int* pathdijk, int startNode[]){
  int* instruction = (int*)malloc(50*sizeof(int));
  for(int j = 0; j < 50; j++){
    instruction[j] = -1;
  }

  int indiceCurrentNode = indicePath(pathdijk);
  char dirCurrent = deterDir(startNode);
  int indiceNextNode = indiceCurrentNode - 1;
  int indiceInstruction = 1;
  instruction[0] = 0;
  while(indiceCurrentNode != 0){
    // Serial.print(dirCurrent);
    // Serial.print("          ");
    // Serial.print(indiceInstruction);
    // Serial.print("          ");
    // Serial.print(instruction[indiceInstruction]);
    // Serial.print("          ");
    // Serial.print(pathdijk[indiceCurrentNode]);
    // Serial.print("          ");
    // Serial.println(pathdijk[indiceNextNode]);

    if(pathdijk[indiceCurrentNode] - 1 == pathdijk[indiceNextNode]){
      if (dirCurrent == 'G')
      {
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'G';
      }
      else if (dirCurrent == 'H')
      {
        instruction[indiceInstruction] = 1;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'G';
      }
      else if (dirCurrent == 'B')
      {
        instruction[indiceInstruction] = 2;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'G';

      }
    }
  
    else if(pathdijk[indiceCurrentNode] + 1 == pathdijk[indiceNextNode]){
      if (dirCurrent == 'D')
      {
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'D';
      }
      else if (dirCurrent == 'H')
      {
        instruction[indiceInstruction] = 2;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'D';
      }
      else if (dirCurrent == 'B')
      {
        instruction[indiceInstruction] = 1;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'D';

      }
  
    }
    else if(pathdijk[indiceCurrentNode] - 6 == pathdijk[indiceNextNode]){
      if (dirCurrent == 'H')
      {
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'H';
      }
      else if (dirCurrent == 'G')
      {
        instruction[indiceInstruction] = 2;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'H';
      }
      else if (dirCurrent == 'D')
      {
        instruction[indiceInstruction] = 1;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'H';

      }
  
    }
    else if(pathdijk[indiceCurrentNode] + 6 == pathdijk[indiceNextNode]){
      if (dirCurrent == 'B')
      {
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'B';
      }
      else if (dirCurrent == 'G')
      {
        instruction[indiceInstruction] = 1;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'B';
      }
      else if (dirCurrent == 'D')
      {
        instruction[indiceInstruction] = 2;
        indiceInstruction++;
        instruction[indiceInstruction] = 0;
        indiceInstruction++;
        dirCurrent = 'B';

      }
    }
    indiceCurrentNode--;
    indiceNextNode--;
  }
  return instruction;
  

}

bool isNodeInPath(int* pathdijk, int shortNode[]){
  for(int i = 0; i < 36; i++){
    if(shortNode[0] == pathdijk[i]){
      return 1;
    }
  }
  return 0;
}

// 0
// 0 
// 8 
// 2 
// 5 
// 11 
// 12 
// 1 
// 9 
// 10 
// 4 
// 17 
// 18 
// 7 
// 13 
// 14 
// 15 
// 16 
// 24 
// 18 
// 19 
// 20 
// 23 
// 17 
// 30 
// 19 
// 27 
// 28 
// 22 
// 23 
// 31 
// 32 
// 26 
// 34 
// 35 
// 29

// 29-23-17-16-15-14-13-7-1-0
