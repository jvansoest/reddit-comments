#include "simdjson.h"

std::vector<std::string_view> SplitSV(const std::string_view str, const char delim = ' ')
{   
    std::vector<std::string_view> result;

    int indexCommaToLeftOfColumn = 0;
    int indexCommaToRightOfColumn = -1;

    for (int i=0;i<static_cast<int>(str.size());i++)
    {
        if (str[i] == delim)
        {
            indexCommaToLeftOfColumn = indexCommaToRightOfColumn;
            indexCommaToRightOfColumn = i;
            int index = indexCommaToLeftOfColumn + 1;
            int length = indexCommaToRightOfColumn - index;

            // Bounds checking can be omitted as logically, this code can never be invoked 
            // Try it: put a breakpoint here and run the unit tests.
            /*if (index + length >= static_cast<int>(str.size()))
            {
                length--;
            }               
            if (length < 0)
            {
                length = 0;
            }*/

            std::string_view column(str.data() + index, length);
            result.push_back(column);
        }
    }
    const std::string_view finalColumn(str.data() + indexCommaToRightOfColumn + 1, str.size() - indexCommaToRightOfColumn - 1);
    result.push_back(finalColumn);
    return result;
}




int main(void) {
  simdjson::dom::parser parser;
  simdjson::dom::element tweets = parser.load("twitter.json");
  std::cout << tweets["search_metadata"]["count"] << " results." << std::endl;
  
  simdjson::dom::parser parser2;
  simdjson::dom::document_stream docs = parser2.load_many("RC_2006-12");
  for (simdjson::dom::element doc : docs) {
      std::cout << doc["created_utc"] << std::endl;
      std::string_view body  = doc["body"].get_string();
      std::cout << body << std::endl;
      std::vector<std::string_view> tokens = SplitSV(body, ' ');	
      
      for (int i = 0; i<tokens.size(); i++){
         std::cout << body.at(i) << ' ';
      }


  }


}
