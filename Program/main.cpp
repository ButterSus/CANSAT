/**
 * @author ButterSus
 * @date June 2022
 */

void setup();

int main(){
    asm volatile("sei");
    setup();
    while(1);
}
