# maeze solver(adachi method)

## introduce 
* maze size =16*16
```
uint8 maze[16][16];  // input wall exist data and came data.
uint8 dist[16][16];  // input distance for goal
```

## Adachi method 

`Adachi Method` is specialized for micromouse as maze solver.
It is based on DFS algorithm.

this document explain about this method.

this method made up of 6step.

### overview 

```
search start 
 loop 
   0. if you reached goal break.
   1. get sensor data
   2. input matrix for distance map
   3. update distance map
   4. select next cell
   5. move your mouse selected cell
   next loop
```


## Step1 (getting data)

Getting sensor data with A/D converter,
and detect exist wall.

```cpp
// sensor.left is sensor raw data getting by A/D convertor.
bool exist_left_side_wall = sensor.left > sensor_threathold.left;

// input data 
input_wall_data(uint8 x,uint8 y,uint8 direction, bool exist);
```

## Steo2 (input data in matrix)

```cpp
/**
 *  input wall data 
 *  @param x: update cell of x
 *  @param x: update cell of y
 *  @param direction  :update cell of direction
 *  @param exist : true / false(not exist)
 *  // data format is 0xff
 *  //                   S W E N | S W E N  <- this character means write below.
 *  //                   0 0 0 0 | 0 0 0 0
 *  // <-4bit is confirmed  flag |  4bit is wall exist flag ->
 *  // N : North = 0x01
 *  // E : East  = 0x02
 *  // W : West  = 0x04
 *  // S :South  = 0x08
 * 
 *  // ex) input input_wall_data(3,1,North,true)
 *  // you should this data convert to below
 *  // map[3][1] |= 0x11;
 */

void input_wall_data(uint8 x,uint8 y,uint8 direction, bool exist){

	if (x < 0 || x >= MAZE_SIZE || y < 0 || y >= MAZE_SIZE) {
		return;
	}
	map[x][y] |= (0x10 * dir); // if you input 8(south), 0x80
	if (isWall) {
		map[x][y] |= 0x01 * dir;
	} else {
		map[x][y] = (map[x][y] & 0xf0) | (map[x][y] & (~(0x01 * dir) & 0x0f));
	}
}
```

## step3 (update distance map)

`distance map` is `matrix data of distance information to goal`.  
It is based on DFS, Goal distance is 0.
So, your robots should follow to this distance number to be lower.

```cpp
//reflesh
for(uint8 i=0;i<16;i++){
    for(uint8 j=0;j<16;j++){
        dist[i][j]=255; //255 = max value of 16*16 size maze.
    }
}

// goal cell to be 0.
dist[7][7]=0; // ex) (7,7) is goal.

// update this search algo O(n^3) too heavy.
// but there is more faster algo
for(uint8 d=0;d<255;d++){
    bool update = false;
    for(uint8 i=0;i<16;i++){
        for(uint8 j=0;j<16;j++){
            tmp_dist = dist[i][j];
            if (tmp_dit == d){
                // if (i,j)'s north wall is not exist (i,j+1)'s dist = (i,j)+1
                
                // if (i,j)'s east wall is not exist (i+1,j)'s dist = (i,j)+1
                
                // if (i,j)'s west wall is not exist (i-1,j)'s dist = (i,j)+1
                
                // if (i,j)'s south wall is not exist (i,j-1)'s dist = (i,j)+1
                update=true;
            }
        }
    }
    if(!update){
        break; //end
    }
}


```

## step4 (select next cell)

find around your cell and select next cell.

```
your mouse is putting (2,2).
candidate cell is (2,3),(3,2),(1,2),(2,1)
but your wall matrix data on wall[2][2] is 0xf6, // "f" is proof of you came (2,2)
just mean exist East and West wall.
so your robots can select only (2,3),(2,1)
and 
if dist[2][3] is 15, dist[2][1] is 11
your robots should select (2,1) ,
so go to South!!

```


