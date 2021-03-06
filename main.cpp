#include <iostream>
#include <list>
#include <stack>

using namespace std;
/*
//val coverages = List( Cov(1, 20), Cov(21, 30), Cov(15, 25), Cov(28, 40), Cov(50, 60), Cov(61, 200)
*/

class Coverage 
{ 
    public:	
    
        //default constructor
        Coverage():m_startDay(0),m_endDay(0) {}
    
        //Constructor
        Coverage(int start, int end):m_startDay(start),m_endDay(end) {}
	
	    //Copy constructor
        Coverage(const Coverage& cov) {
            m_startDay = cov.m_startDay;
             m_endDay = cov.m_endDay;
        }
	
	    //Setters and getters
        int getStartDay() {return m_startDay;}
        void setStartDay(int start) {m_startDay = start;}
        
        int getEndDay() {return m_endDay;}
        void setEndDay(int end) {m_endDay = end;}
        
        int getCoverageInterval() { return m_endDay - m_startDay;}
        
        //Operators
        friend bool operator < (Coverage const &c1, Coverage const &c2) {
            return c1.m_startDay < c2.m_startDay ;
        }
        
        Coverage& operator=(const Coverage& c) {
            this->m_startDay = c.m_startDay;
            this->m_endDay = c.m_endDay;
            return *this;
        }
       
    private:
        int m_startDay;
        int m_endDay; 
       
}; 
  

// The main function that takes a list of coverages, flattering overlapping coverages and returns the largest one 
Coverage getLongestCoverage(list<Coverage>& coverages) 
{ 
      Coverage longestCoverage;
    // if we have at least one coverage interval
    if (coverages.size() <= 0) 
        return longestCoverage; 
  
   //sotre the longest coverage in this memebr
    longestCoverage = *coverages.begin();
  
    // Create an empty stack of coverages 
    stack<Coverage> s; 
  
    // sort the coverages in increasing order of start time (will use our < operator) O(nlogn)
    coverages.sort();
      // push the first Coverage to stack 
    s.push(*coverages.begin()); 
    
    list<Coverage>::iterator it;
     // Start from the next interval and merge if necessary  O(n)
   for (it=coverages.begin(); it!=coverages.end(); ++it)
    { 
        // get Coverage from stack top 
        Coverage top(s.top()); 
        // if current Coverage is not overlapping with stack top, 
        // push it to the stack 
        if (top.getEndDay() + 1 < (*it).getStartDay())  {
            s.push(*it); 
            //store the new coverage into the top so we will be able to compare it later
            top = (*it); 
        }
        // Otherwise update the ending date of top if ending of current coverage is more 
        else if (top.getEndDay() < (*it).getEndDay())  { 
            top.setEndDay((*it).getEndDay()); 
            //remove from top
            s.pop(); 
            //add back
            s.push(top); 
        } 
         //if new coverage interval bigger then current longest one
        if (longestCoverage.getCoverageInterval() < top.getCoverageInterval()) {
            longestCoverage = top;
        }
    } 
  
    return longestCoverage; 
} 

int main(void){
    //input section
   list<Coverage> inputCoverages = {Coverage(1, 20), Coverage(21, 30), Coverage(15, 25), Coverage(28, 40), Coverage(50, 60), Coverage(61, 200)};
   // input END
  Coverage longestCoverage = getLongestCoverage(inputCoverages);
  cout << longestCoverage.getStartDay() << "," << longestCoverage.getEndDay() << endl;
}
