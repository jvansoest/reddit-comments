#include "simdjson.h"
#include <map>

int main(void) {
  //simdjson::dom::parser parser;
  //simdjson::dom::element tweets = parser.load("twitter.json");
  //std::cout << tweets["search_metadata"]["count"] << " results." << std::endl;
  
  simdjson::dom::parser parser2;
  simdjson::dom::document_stream docs = parser2.load_many("RC_2006-12");


  std::map<std::string, int> counts;

  for (simdjson::dom::element doc : docs) {
      //std::cout << doc["created_utc"] << std::endl;
      std::string_view str  = doc["body"].get_string();
      //std::cout << body << std::endl;
            
      std::string word = "";

      for (int i = 0; i<str.size(); i++){

         // check if current char is blank space then it means we got one word
	if (str[i] == ' '){

	  // if the current word is not found then insert current word with freq 1
          if (counts.find(word) == counts.end()){
	    counts.insert(std::make_pair(word, 1));
	    word = "";
	  }

	  //update the frequency
	  else {
	    counts[word]++;
	    word = "";
	  }
        } else {
	 word += str[i];	
        }
     }
     // storing the last word of the string
     if (counts.find(word) == counts.end()){
       counts.insert(std::make_pair(word, 1));
     } else {
       counts[word]++;	
     }

     // traverse the map to print the frequency
     /*for (auto& it: counts){
       std::cout << it.first << " - " << it.second << std::endl;
     }*/

  }









}
