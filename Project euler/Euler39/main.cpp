#include <iostream>

int main(int argc, char **argv) {
  int i3;
  int solutions;					//Number of solutions
  int maxSolutions=0;					//Largets numbers of solutions
  for(int p=840; p<=840; p++)
  {
    solutions=0;					//Reset solutions for this p
    for(int i=p-2; i>p/3; i--)				//from p to p/3 (i has to be biggest)
    {
      for(int i2=p-i-1; i2>=p-i-i2; i2--)			//from i-1 until i3>i2 (i2 has to be bigger or equal to i3)
      {
	i3=p-i-i2;					//i3 gets the rest			
	if(i*i==i2*i2+i3*i3)
	{
	  solutions++;
	  std::cout << "Solution " << solutions << " (" << i << ", " << i2 << ", " << i3 << ")" << std::endl;
	}
      }
    }
    std::cout << "Number of solutions: " << solutions << std::endl;
    if(solutions > maxSolutions)
    {
      maxSolutions=solutions;
      std::cout << "P: " << p << " Solutions: " << solutions << std::endl;
    }
  }
    return 0;
}
