/* MIT. Readable Latin directions with angular Elder Futhark-inspired cuts. */
#ifndef MYRO_COMPASS_LETTERS200_H
#define MYRO_COMPASS_LETTERS200_H
#define COMPASS_LETTERS_X200 176
static const char*const compass_letters200[4][11]={
 {"##.....##",".##....#.",".#.#...#.",".#.#...#.",".#..#..#.",".#..#..#.",".#...#.#.",".#...#.#.",".#....##.",".#.....#.","##.....##"},
 {".#####.",".#.....",".#.....",".####..",".#.....",".#.....",".#.....",".#####.",".......",".......","......."},
 {"..####.",".#.....",".#.....","..##...","....##.",".....#.",".....#.",".####..",".......",".......","......."},
 {"#...#...#","#...#...#","#...#...#","#...#...#",".#.#.#.#.",".#.#.#.#.",".#.#.#.#.","..#...#..",".........",".........","........."}
};
static void compass_letters_init200(unsigned*p){for(unsigned i=0;i<4;i++){
 unsigned x0=COMPASS_LETTERS_X200+i*16,w=(i==0||i==3)?9:7,h=i==0?11:8,ox=(16-w)/2,oy=(16-h)/2;
 for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++)if(compass_letters200[i][y][x]=='#'){
  for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)p[(1840+oy+y+dy)*512+x0+ox+x+dx]=0xff1b1616;
  p[(1840+oy+y+2)*512+x0+ox+x+1]=0x70000000;
 }
 for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++)if(compass_letters200[i][y][x]=='#')p[(1840+oy+y)*512+x0+ox+x]=i==0?0xffed4f58:0xfffff3dc;
}}
#endif
