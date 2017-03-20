#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define tableSize 4

struct Node;
typedef struct Node node;
struct Table;
typedef struct Table table;

int step = 0;

struct Node{
    int x;
    int y;
    bool left;
    bool up;
    bool right;
    bool down;
    bool isVisited;
};

struct Table{
    node t[tableSize][tableSize];
};

table initialise(){
    int i, j;
    
    table maze = {};
    
    for (i = 0; i < tableSize; i++){
        for (j = 0; j < tableSize; j++){
            node a;
            if (j == 0) {a.up = false;} else {a.up = true;}
            if (j == tableSize - 1) {a.down = false;} else {a.down = true;}
            if (i == 0) {a.left = false;} else {a.left = true;}
            if (i == tableSize - 1) {a.right = false;} else {a.right = true;}
            
            a.x = i;
            a.y = j;
            a.isVisited = false;
            
            maze.t[i][j] = a;
        }
    }
    return maze;
}

void setFalse(node* a, int direction){   //TEST FUNCTION
    switch (direction){
        case 1: a -> up = false; break;
        case 2: a -> down = false; break;
        case 3: a -> left = false; break;
        case 4: a -> right = false; break;
        default: break;
    }
}


node*** newQueue(int path, int step){
    node*** a;
    a=(node ***) malloc(path * sizeof(node**));
    
    for(int i = 0; i < path; i++)
        a[i]=(node **) malloc(step * sizeof(node*));
    
    return a;
}

node** pathSearch(table maze){
    step = 1;
    
    int ppc, cpc, final_path = -1;
    int i, j;
    bool isFound = false;
    node*** pre;
    node*** temp = newQueue(1, step);
    
    temp[0][0] = &maze.t[0][tableSize - 1];
    maze.t[0][tableSize - 1].isVisited = true;
    cpc = 1;
    
    while(isFound == false){
        ppc = cpc;
        cpc = 0;
        

        pre = newQueue(ppc, step);
        for (i = 0; i < ppc; i++){
            for (j = 0; j < step; j++){
                pre[i][j] = temp[i][j];
            }
        }
        
        free(temp);
        
        temp = newQueue(100, step + 1);
        
        for (i = 0; i < ppc; i++){
            
            node* a = pre[i][step - 1];
            int x = a -> x;
            int y = a -> y;
            
            if (a -> left == true){
                node* b = &maze.t[x - 1][y];
                if (b -> isVisited == false){
                    for (j = 0; j < step; j++){
                        temp[cpc][j] = pre[i][j];
                    }
                    temp[cpc][step] = b;
                    b -> isVisited = true;
                    cpc++;
                }
                
                if (b -> x == tableSize - 1 && b -> y == 0){
                    isFound = true;
                    final_path = cpc;
                    break;
                }
            }
            
            if (a -> right == true){
                node* b = &maze.t[x + 1][y];
                if (b -> isVisited == false){
                    for (j = 0; j < step; j++){
                        temp[cpc][j] = pre[i][j];
                    }
                    temp[cpc][step] = b;
                    b -> isVisited = true;
                    cpc++;
                }
                
                if (b -> x == tableSize - 1 && b -> y == 0){
                    isFound = true;
                    final_path = cpc;
                    break;
                }
            }
            
            if (a -> up == true){
                node* b = &maze.t[x][y - 1];
                if (b -> isVisited == false){
                    for (j = 0; j < step; j++){
                        temp[cpc][j] = pre[i][j];
                    }
                    temp[cpc][step] = b;
                    b -> isVisited = true;
                    cpc++;
                }
                
                if (b -> x == tableSize - 1 && b -> y == 0){
                    isFound = true;
                    final_path = cpc;
                    break;
                }
            }
            
            if (a -> down == true){
                node* b = &maze.t[x][y + 1];
                if (b -> isVisited == false){
                    for (j = 0; j < step; j++){
                        temp[cpc][j] = pre[i][j];
                    }
                    temp[cpc][step] = b;
                    b -> isVisited = true;
                    cpc++;
                }
                
                if (b -> x == tableSize - 1 && b -> y == 0){
                    isFound = true;
                    final_path = cpc;
                    break;
                }
            }
        }
        
        free(pre);
        step++;
    }
    
    node** best_path = (node** )malloc(step * sizeof(node*));
    if (final_path != -1){
        for (j = 0; j < step; j++){
            best_path[j] = temp[final_path - 1][j];
        }
    }
    else{
        return NULL;
    }
    
    return best_path;
}

void walkPath(node* current, node* next){
    int dif_X, dif_Y;
    
    dif_X = (next -> x) - (current -> x);
    dif_Y = (next -> y) - (current -> y);
    
    switch (dif_X) {
        case 1:
            //moveRight();
            printf("Move Right\n");
            break;
        case -1:
            //moveLeft();
            printf("Move Left\n");
        default:
            break;
    }
    
    switch (dif_Y) {
        case 1:
            //moveDown();
            printf("Move Down\n");
            break;
        case -1:
            //moveUp();
            printf("Move Up\n");
            break;
        default:
            break;
    }
    
}

int main(){                                    // Main function
    table maze = initialise();
    
    setFalse(&maze.t[0][3], 1);
    setFalse(&maze.t[0][2], 2);
    setFalse(&maze.t[0][1], 4);
    setFalse(&maze.t[1][0], 2);
    setFalse(&maze.t[1][1], 1);
    setFalse(&maze.t[1][1], 3);
    setFalse(&maze.t[1][2], 4);
    setFalse(&maze.t[2][1], 4);
    setFalse(&maze.t[2][2], 3);
    setFalse(&maze.t[2][2], 4);
    setFalse(&maze.t[2][2], 2);
    setFalse(&maze.t[2][3], 1);
    setFalse(&maze.t[3][0], 2);
    setFalse(&maze.t[3][1], 1);
    setFalse(&maze.t[3][1], 3);
    setFalse(&maze.t[3][2], 3);
    
    node** best_path = pathSearch(maze);
     
    for (int i = 0; i < step - 1; i++){
        node* current = best_path[i];
        node* next = best_path[i + 1];
        walkPath(current, next);
    }
    
    
    return 0;
}
