#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 0) {
    return 0;
  }
  int pre = array[0];
  int totalNum = 1;
  int bestNum = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > pre) {
      totalNum += 1;
      if (totalNum > bestNum) {
        bestNum = totalNum;
      }
    } else {
      totalNum = 1;
    }

    pre = array[i];
  }
  return bestNum;
}

//int main(void) {                                                                                                     
// if (maxSeq(NULL, 0)) {                                                                                              
//   return EXIT_FAILURE;                                                                                              
// }                                                                                                                   
// int array1[] = {1, 2, 3, 2};                                                                                        
// int array2[] = {2, -3, 5, 6, 8};                                                                                    
// int array3[] = {5};                                                                                                 
// int array4[] = {2, 4, 3, 6, 10, 15, -1, 7, 8, 2};                                                                   
// int array5[] = {-2};                                                                                                
// int array6[] = {2,2,2,3};                                                                                           
// if (maxSeq(array1, 0)) {                                                                                            
//   printf("not good!\n");                                                                                            
//   return EXIT_FAILURE;                                                                                              
// }                                                                                                                   
// if (maxSeq(array1, 4) != 3) {                                                                                       
//   printf("not good!\n");                                                                                            
//   return EXIT_FAILURE;                                                                                              
// }                                                                                                                   
// if (maxSeq(array2, 5) != 4) {     
//   printf("not good!\n");                                                                                            
//   return EXIT_FAILURE;                                                                                              
// }                                                                                                                   
// if (maxSeq(array3, 1) != 1) {                                                                                       
//   printf("not good!\n");                                                                                            
//   return EXIT_FAILURE;                                                                                              
// }                                                                                                                   
// if (maxSeq(array4, 10) != 4) {                                                                                      
//   printf("not good!\n");                                                                                            
//   return EXIT_FAILURE;                                                                                              
// }       
