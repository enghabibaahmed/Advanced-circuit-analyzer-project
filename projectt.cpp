#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//check if a number is digit
bool isdigit ( char c)
{ return (c >= '0' && c <= '9');
}

//convert character into number
double chartoint ( char c)
{ return (c-'0');
}

//calculate the series equivalent resistance
double calculateseries ( string x )
{ double total_series=0; //a variable that will include the equivalent resistance result
int n=0; //a variable to count the number of resistors
    for ( int i=0 ; i<x.length() ; i++)
     {
         if ( x[i]==' ' || x[i]==',') //not a digit
         continue;
       if(isdigit(x[i]))
         { double number = chartoint(x[i]); //a single digit
           n++;
              if ( i+1<x.length() && isdigit(x[i+1]) && !isdigit(x[i+2]) ) //in case of 2 digit number
            {  number= number*10 + chartoint(x[i+1]);
                i++;
            }
              if ( i+1<x.length() && isdigit(x[i+1]) && isdigit(x[i+2]) ) //in case of 3 digit number
            {  number= number*100 + chartoint(x[i+1])*10 + chartoint(x[i+2]);
                i+=2;
            }

              if ( x[i+1]=='.' && i+1 < x.length() ) //in case of decimal number
              { number= number + chartoint(x[i+2])/10;
              i+=2;
              }
              total_series+=number; //equivalent resistance= sum of all resistors
         }
    }
    if ( (n==0)) //series connection must have one or more resistors
 {cout<< "Incorrect Input"<<endl;
               exit(0);} //display an error message and close instantly

return total_series;
}

//calculate the parallel equivalent resistance
double calculateparallel(string y)
{ double inverse_parallel=0; //the reciprocal of the equivalent parallel resistance
 int n=0;  //a variable to count the number of resistors
for ( int i=0 ; i<y.length() ; i++)
     {
         if ( y[i]==' ' || y[i]==',') //not a digit
         continue;
       if(isdigit(y[i]))
         {  n++;
            double number = chartoint(y[i]); //a single digit
              if ( i+1<y.length() && isdigit(y[i+1]) && !isdigit(y[i+2])) //in case of 2 digit number
                 {    number= number*10 + chartoint(y[i+1]);
                      i++;
                      inverse_parallel+=1/number;
                      continue; }
              if ( i+1<y.length() && isdigit(y[i+1]) && isdigit(y[i+2]) ) //in case of 3 digit number
                 {  number= number*100 + chartoint(y[i+1])*10 + chartoint(y[i+2]);
                     i+=2;
                     inverse_parallel+=1/number;
                     continue; }
              if ( y[i+1]=='.' && i+1 < y.length() ) //in case of decimal number
                 { number= number + chartoint(y[i+2])/10;
                    i+=2;
                    inverse_parallel+=1/number;
                    continue;}
        inverse_parallel+=1/number;
         }
    }
 if ((n==0) || (n==1)) //parallel connection must have two or more resistors
 {cout<< "Incorrect Input"<<endl;
               exit(0);} //display an error message and close instantly
 return 1/inverse_parallel;
}

//main function
int main() {
//initial declaration of variables
    string input, x="",y="",news="" , newp="";
    double result, series,parallel ;
    int h = -1, a = -1 , b = -5, c = -5 , n = 0 , end , start , o=-1,u=-1;
 //get the circuit description from user
    getline(cin, input);

//handle error of wrong description
    for ( int i = 0; i < input.length(); i++ )
    { string valid="SsPp .,e"; //all valid characters that can be included in the input
       if ( valid.find(input[i])==string::npos && !isdigit(input[i])){ //if a character in the string is not from the valid characters and is not a digit
        cout<<"Wrong Description"<<endl;
        exit(0); //display an error message and exit the program instantly
       }
       if ( input[i]== 'e')
        n++; //count how many e exists in the input to check how many connections is there
    }
//in case of nested circuit
 if ( n> 1)
{
    for ( int i = input.length()-1 ; i>=0 && n>1 ; i--) //walk through the string from right to left to extract the first sub circuit to solve
{
    if (input[i]== 'S' || input [i]=='s') //when i found the first s, i start moving from left to right
        { start=i;
          end = input.find('e' , start); //finding the e of this sub circuit to know where it ends
           news= input.substr( start+1 , end - start -1 ); //extract this sub circuit
           series= calculateseries(news); //calculate the equivalent resistance of the sub circuit

              input.replace( start , end- start +1 , to_string((int)series) ); //replace this sub circuit in the string with its equivalent resistance value
              n--; //total number of connections is reduced by 1
        }
    if(input[i]== 'P' || input [i]=='p') //when i found the first p, i start moving from left to right
        { start = i;
        end= input.find('e' , start); //finding the e of this sub circuit to know where it ends
          newp= input.substr( start+1 , end - start - 1); //extract this sub circuit
           parallel=calculateparallel(newp); //calculate the equivalent resistance of the sub circuit

           input.replace( start , end - start +1 , to_string((int)parallel) ); //replace this sub circuit in the string with its equivalent resistance
           n--;  //total number of connections is reduced by 1
            }
}
}
//i have only one connection left
   if ( n==1)
   { for (int i = 0; i < input.length(); i++) {
        if (input[i] == 'S' || input[i] == 's') {
            h = i;
        }
        if (input[i] == 'e') {
            a = i;
        }
        if (h != -1 && a != -1) //they don't keep their initial values which means the last 2 conditions is true
           { o++;
               x = input.substr(h + 1, a - h - 1); //extract the resistance values
              series= calculateseries(x); //calculate the equivalent resistance
            break;
            }
    }
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == 'P' || input[i] == 'p') {
            b = i;
        }
        if (input[i] == 'e') {
            c = i;
        }
        if (b != -5 && c != -5) //they don't keep their initial values which means the last 2 conditions is true
           { u++;
               y= input.substr(b+1, c-b-1); //extract the resistance values
           parallel= calculateparallel(y); //calculate the equivalent resistance
            break;
            }
    }
if ( o == 0 ) //it means the last connection was series
   { result = series; }
else if ( u ==0 ) //it means the last connection was parallel
    { result= parallel ;}

//display the equivalent resistance value
cout<< "The total resistance = " << result << endl;
   }
    return 0; //to exit the program
}
