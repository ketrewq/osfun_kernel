#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/linkage.h>

#define MAX_SIZE 100      // 스택의 최대 크기는 100

int data[MAX_SIZE] = {0,};      // 초기화 
int top = -1;      // 포인터의 역할 

SYSCALL_DEFINE1(os_push, int, val){       // 조건 1. int 변수를 인자로 가짐.
        while (val > 0) {  
                int flag = 0;    // flag 라는 변수를 통해서 중복되는 값의 유무를 구분 
                printk("inserting %d\n", val % 10);
                if (top == MAX_SIZE) {
                        printk("error: this causes an overflow!\n");
                        return -1;      // 오버플로우 방지 
                }
                int i = 0, j = 0;
                while (i <= top) {
                        if (data[i] == val % 10) {
                                printk("error: %d is already in the stack.\n", val % 10);
                                flag = 1;       
                                break;          // 조건 2. 추가하려는 값이 이미 stack에 있으면 추가하지 않음
                        }
                i++;       // while loop을 위해 더해줌
                }
                if (flag) {
                        printk("\npassing this operation\n\n");
                }
                else{
                        top++;    
                        data[top] = val % 10;        // ex) 123 넣었으면 3부터 들어감 
                        printk("===top===\n");       // dmesg에 로그 출력하는 포맷 
                        while (j <= top) {
                                printk(">  %d\n", data[top - j]);
                                j++;
                }   
                printk("==bottom==\n\n");
        }
        val /= 10;  // while loop을 위해 나눠줌 
    }
    return 0;
}

SYSCALL_DEFINE0(os_pop){      // 인자로 아무것도 가지지 않음 
        int i = 0;
        if (top == -1) {
                printk("error: this causes an underflow!\n");
                return -1;      
                // 언더플로우 방지. 만약에 중복된 숫자를 넣었다면, 마지막에서 underflow발생, -1 리턴 
        }

        int last = data[top];    // 리턴해야하는 숫자
        top--;       // 조건 3. 가장 나중에 들어온 값을 stack에서 제거, 그 값을 return 

        printk("popping %d\n", last);
        printk("===top===\n");
        while (i <= top) {
                printk(">  %d\n", data[top - i]);       
                i++;
        }
        printk("==bottom==\n\n");

        return last;         // pop되는 숫자를 리턴 
}