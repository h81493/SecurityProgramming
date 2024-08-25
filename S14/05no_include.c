// https://qiita.com/lzpel/items/1ab9469bc24d6ce6b00e
// gcc -static -nostdlib no_include.c
void _start(void){
   const char mes[] = "hello, world\n";
   __asm __volatile(
       "lea %2,%%rsi;syscall"
        :
        :"a"(1), "D"(1), "m"(mes), "d"(sizeof(mes) - 1)
        :"rsi"
   );
   __asm __volatile(
       "syscall"::"a"(60), "D"(1)
   );
}
