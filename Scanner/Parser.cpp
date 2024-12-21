#include <bits/stdc++.h>
using namespace std;

bool checkSimple(string one ,string two){
    // Only B , S are the allowed non-terminals
    for(char i : one){
        if(i >= 'A' and i <= 'Z')
            if(i != 'B' and i != 'S')return false;
    }
    
    for(char i : two){
        if(i >= 'A' and i <= 'Z')
            if(i != 'B' and i != 'S')return false;
    }
    
    if(one.empty() or two.empty())return false;
    
    // check if first char is diffrent for the same non-terminal rules
    if((one[0] >= 'a' and one[0] <='z') and (two[0] >= 'a' and two[0] <='z'))
      if(one[0] != two[0])return true;
      
  return false;
}



int main() 
{
    cout << "The Two accepted non-terminal are S , B ";
    cout << endl;
    
    string Stack;
    string s1 , s2 , b1 , b2;
    string reverseds1 , reverseds2 , reversedb1 , reversedb2;
    string input;

    while(1){
      cout << "Enter rule 1 of S : "; cin >> s1;
      cout << "Enter rule 2 of S : "; cin >> s2;
      cout << "Enter rule 1 of B : "; cin >> b1;
      cout << "Enter rule 2 of B : "; cin >> b2;

      if( not (checkSimple(s1 , s2) and checkSimple(b1 , b2) )){
        cout << "This is Wrong grammar , Rewrite the rules" << endl;
        continue;
      }
      
      reverseds1 = s1;
      reverseds2 = s2;
      reversedb1 = b1;
      reversedb2 = b2;
      
      reverse(reverseds1.begin() , reverseds1.end());
      reverse(reverseds2.begin() , reverseds2.end());
      reverse(reversedb1.begin() , reversedb1.end());
      reverse(reversedb2.begin() , reversedb2.end());
      anotherString:;
      cout << "Enter input string : ";
      cin >> input;
      cout << "The input string : "; 
      cout << '[';
      for(char i : input) cout << i << " ";
      cout << ']';

      cout<< endl;
      Stack.push_back('S');
      int i = 0 ;
      for(; i < input.size() and not Stack.empty() ; i++){
          if(Stack.back() == 'S'){
              if(input[i] == s1[0]){
                Stack.pop_back();
                for(char c : reverseds1)Stack.push_back(c);
                i--;
              }else if(input[i] == s2[0]){
                Stack.pop_back();
                for(char c : reverseds2)Stack.push_back(c);
                i--;
              }else{
                  break;
              }
          }else if(Stack.back() == 'B'){
              if(input[i] == b1[0]){
                Stack.pop_back();
                for(char c : reversedb1)Stack.push_back(c);
                i--;
              }else if(input[i] == b2[0]){
                Stack.pop_back();
                for(char c : reversedb2)Stack.push_back(c);
                i--;
              }else{
                  break;
              }
          }else if(Stack.back() == input[i]){
              Stack.pop_back();
          }
      }
      string ans ;
      if(Stack.empty() and i == input.size()){
         ans = "Accepted";
      }else{
          ans = "Rejected";
      }
      cout << "Stack after check : ";
      cout << '[';
      for(char i : Stack)cout << i << " ";
      cout << ']';
      cout << endl;
      
      cout << "Rest of unchecked input : ";
      
      cout << '[';
      for(; i < input.size() ; i++)cout << input[i] << " ";
      cout << ']';
      cout << endl;
      
      cout << "Your string is " << ans;
      cout << endl << "=======================================================";
      cout << endl;
      cout << "1.Another Grammar \n2.Another string\n3.Exit\n";
      int want; cin >> want;
      if(want == 1){
          continue;
      }else if(want == 2){
          goto anotherString;
      }else{
          break;
      }
    }
    return 0;
}
