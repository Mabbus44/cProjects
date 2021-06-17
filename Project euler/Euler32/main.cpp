#include <iostream>

int main(int argc, char **argv) {
    int numA[4];
    int numB[2];
    int product[4];
    int productVals[1000];
    int productVal;
    int productValCount;
    int sum;
    int temp;
    int i;
    bool ok;
    
    productValCount=0;
    numA[0]=1;
    while(numA[0]<10)
    {
      numA[1]=1;
      while(numA[1]<10)
      {
	while(numA[1]==numA[0])
	  numA[1]++;
	if(numA[1]>9)
	  continue;
	numA[2]=1;
	while(numA[2]<10)
	{
	  while(numA[2]==numA[0]||numA[2]==numA[1])
	    numA[2]++;
	  if(numA[2]>9)
	    continue;
	  numB[0]=1;
	  while(numB[0]<10)
	  {
	    while(numB[0]==numA[0]||numB[0]==numA[1]||numB[0]==numA[2])
	      numB[0]++;
	    if(numB[0]>9)
	      continue;
	    numB[1]=1;
	    while(numB[1]<10)
	    {
	      while(numB[1]==numA[0]||numB[1]==numA[1]||numB[1]==numA[2]||numB[1]==numB[0])
		numB[1]++;
	      if(numB[1]>9)
		continue;
	      productVal=(numA[0]*100+numA[1]*10+numA[2])*(numB[0]*10+numB[1]);
	      if(productVal>9999||productVal<1000)
	      {
		numB[1]++;
		continue;
	      }
	      temp=productVal;
	      for(i=3;i>=0;i--)
	      {
		product[i]=(temp%10);
		temp=temp/10;
	      }
	      ok=true;
	      for(i=0;i<=3;i++)
		if(product[i]==numA[0]||product[i]==numA[1]||product[i]==numA[2]||product[i]==numB[0]||product[i]==numB[1]||product[i]==0)
		  ok=false;
	      if(product[0]==product[1]||product[0]==product[2]||product[0]==product[3]||product[1]==product[2]||product[1]==product[3]||product[2]==product[3])
		ok=false;
	      for(i=0;i<productValCount;i++)
		if(productVal==productVals[i])
		  ok=false;
	      if(ok&&productValCount<1000)		//If ok then add number
	      {
		productVals[productValCount]=productVal;
		productValCount++;
		std::cout << productValCount << ": " << numA[0] << numA[1] << numA[2] << " * " << numB[0] << numB[1] << " = " << product[0] << product[1] << product[2] << product[3] << " " << productVal << std::endl;
	      }
	      //std::cout << numA[0] << numA[1] << numA[2] << " * " << numB[0] << numB[1] << " = " << productVal << std::endl;
	      numB[1]++;
	    }
	    numB[0]++;
	  }
	  numA[2]++;
	}
	numA[1]++;
      }
      numA[0]++;
    }

    
    
    
    
    
    
    
    numA[0]=1;
    while(numA[0]<10)
    {
      numA[1]=1;
      while(numA[1]<10)
      {
	while(numA[1]==numA[0])
	  numA[1]++;
	if(numA[1]>9)
	  continue;
	numA[2]=1;
	while(numA[2]<10)
	{
	  while(numA[2]==numA[0]||numA[2]==numA[1])
	    numA[2]++;
	  if(numA[2]>9)
	    continue;
	  numA[3]=1;
	  while(numA[3]<10)
	  {
	    while(numA[3]==numA[0]||numA[3]==numA[1]||numA[3]==numA[2])
	      numA[3]++;
	    if(numA[3]>9)
	      continue;
	    numB[0]=1;
	    while(numB[0]<10)
	    {
	      while(numB[0]==numA[0]||numB[0]==numA[1]||numB[0]==numA[2]||numB[0]==numA[3])
		numB[0]++;
	      if(numB[0]>9)
		continue;
	      productVal=(numA[0]*1000+numA[1]*100+numA[2]*10+numA[3])*(numB[0]);
	      if(productVal>9999||productVal<1000)
	      {
		numB[0]++;
		continue;
	      }
	      temp=productVal;
	      for(i=3;i>=0;i--)
	      {
		product[i]=(temp%10);
		temp=temp/10;
	      }
	      ok=true;
	      for(i=0;i<=3;i++)
		if(product[i]==numA[0]||product[i]==numA[1]||product[i]==numA[2]||product[i]==numA[3]||product[i]==numB[0]||product[i]==0)
		  ok=false;
	      if(product[0]==product[1]||product[0]==product[2]||product[0]==product[3]||product[1]==product[2]||product[1]==product[3]||product[2]==product[3])
		ok=false;
	      for(i=0;i<productValCount;i++)
		if(productVal==productVals[i])
		  ok=false;
	      if(ok&&productValCount<1000)		//If ok then add number
	      {
		productVals[productValCount]=productVal;
		productValCount++;
		std::cout << productValCount << ": " << numA[0] << numA[1] << numA[2] << numA[3] << " * " << numB[0] << " = " << product[0] << product[1] << product[2] << product[3] << " " << productVal << std::endl;
	      }
	      //std::cout << numA[0] << numA[1] << numA[2] << " * " << numB[0] << numB[1] << " = " << productVal << std::endl;
	      numB[0]++;
	    }
	    numA[3]++;
	  }
	  numA[2]++;
	}
	numA[1]++;
      }
      numA[0]++;
    }

    
    
    
    
    
    
    
    
    
    sum=0;
    for(i=0;i<productValCount;i++)
      sum+=productVals[i];
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
