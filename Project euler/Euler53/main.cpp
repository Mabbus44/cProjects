#include <iostream>
#include <stdint.h>




int main(int argc, char **argv) {
  uint64_t n, r, top, bot, ans;
  int count = 0;
  for(n=2; n<=100; n++){
    std::cout << "n: " << n << std::endl;
    r=n;
    ans=0;
    while(r>=n/2 && ans<1000000){
      std::cout << "r: " << r << std::endl;
      top=1;
      for(int i=r+1; i<=n; i++){
	top*=i;
      }
      std::cout << "top: " << top << std::endl;
      bot=1;
      for(int i=1; i<=n-r; i++){
	bot*=i;
      }
      std::cout << "bot: " << bot << std::endl;
      ans=top/bot;
      std::cout << "ans: " << ans << std::endl;
      r--;
    }
    r++;
    if(ans>=1000000){
      count+=(n-1-(n-r-1)*2);
      std::cout << "count: " << count << std::endl;
    }
  }

  std::cout << "Answer: " << count << std::endl;
  return 0;
}
