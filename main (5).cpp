#include <bitset>
#include <iostream>
using namespace std;
bool fullAdder(bool b1, bool b2, bool& carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}
bitset<33> bitsetAdd(bitset<32>& x, bitset<32>& y)
{
    bool carry = false;
    
    bitset<33> ans;
    for (int i = 0; i < 33; i++) {
        ans[i] = fullAdder(x[i], y[i], carry);
    }
    return ans;
}

int main() {
  float a = 0, b = 0;
  std::cout << "ingresa el multiplicando: " << std::endl;
  std::cin >> a;
  std::cout << std::endl;
  
  std::cout << "ingresa el multiplicador: " << std::endl;
  std::cin >> b;
  std::cout << std::endl;
  
  std::bitset<33> bias= false;
  bias[32]=true;
  std::bitset<33> sum1= false;
  
  union {
    float input;
    int output;
  } data;
  data.input = a;
  std::bitset<32> bits1(data.output);
  std::bitset<1> signo1 = false;
  std::bitset<32> expo1 = false;
  std::bitset<32> signif1 = false;

  data.input=b;
  std::bitset<32> bits2(data.output);
  std::bitset<1> signo2 = false;
  std::bitset<32> expo2 = false;
  std::bitset<32> signif2 = false;
  
  float e = 1;
  
  if(bits1[31]){
    signo1=true;
  }
  if(bits2[31]){
    signo1=true;
  }
  
  for (int i = 30, j=31; i > 22; i--,j--) {
    expo1[j]=bits1[i];
  }
  std::cout << expo1 << std::endl;
  for (int i = 22,j=31; i >= 0; i--,j--) {
    signif1[j]=bits1[i];
  }
  std::cout << signif1 << std::endl;

  for (int i = 30, j=31; i > 22; i--,j--) {
    expo2[j]=bits2[i];
  }
  std::cout << expo1 << std::endl;
  for (int i = 22,j=31; i >= 0; i--,j--) {
    signif2[j]=bits2[i];
  }


  if(bits1 == false){
    return 0;
  }
  else if(bits2 == false){
    return 0;   
  }
  else{
    sum1 = bitsetAdd(expo1, expo2);
    bias = (~sum1 & bias) | (sum1 & ~bias);

    if(bias[32]==true){
      cout<< "hay un overflow ";
      return 0 ;
    }
    else if(bias[32]==false) && (sum1[31]==true){
      cout<< "hay un underflow ";
      return 0 ;
    }
    
  }
}