#include "BlackJack.h"
#include <stdlib.h>  
#include <time.h> 
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , 				__FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void test();
int main() {
	
	test();
	cout <<"leaks: "<< _CrtDumpMemoryLeaks();
	
	return 0;
}

void test()
{
	srand(time(NULL));
	BlackJack bj;

	bj.play();
}

