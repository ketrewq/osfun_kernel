#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define __NR_push 335     // os_push, syscall_64.tbl에 정의된 주소 
#define __NR_pop 336      // os_pop

int main(int argc, char *argv[]) {

    int i = atoi(argv[1]);      // 들어오는 string 값을 int 값으로 변환 
    int j = atoi(argv[1]);      // i, j, cnt는 터미널에서 결과값을 출력하기 위해서만 존재 

    syscall(__NR_push, i);      // ex) ./osfun_application 123 은 syscall(335, 123)과 같음 
    for (; i > 0; i /= 10){   
        printf("trying to push %d\n", i % 10); 
    }     // 결과 출력만을 위한 표면적인 코드 

    for (; j > 0; j /= 10){     // -1를 리턴하면 오류가 났다는 뜻임. 
        printf("popping %ld\n", syscall(__NR_pop));      
        // 변수의 정의를 syscall로 하고 쓸 시 여러번 불러지므로, 바로 printf 안에 넣음 
    }
    return 0;
}
