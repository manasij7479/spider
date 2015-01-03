#ifndef SPIDER_PARSER_STREAM_HPP
#define SPIDER_PARSER_STREAM_HPP
#include <vector>
#include <map>
#include <iterator>
#include <istream>
#include <cctype>
namespace spider
{
    class Stream
    {
    public:
        Stream(std::istream& in)
        {
            //Not sure if safe
            //If found not to be, change to a char-by-char rdbuf copying
            
            if (!in.eof() && !in.fail())
            {
                in.seekg(0, std::ios_base::end);
                std::streampos inSize = in.tellg();
                data.resize(inSize);

                in.seekg(0, std::ios_base::beg);
                in.read(&data[0], inSize);//may cause segfault, preserve space in vector
            }
            position = 0;
        }
        Stream(std::string in)
        {
            std::copy(in.begin(), in.end(), std::back_inserter(data));
            position=0;
        }
        int pos(){return position;}
        char get()
        {
            if(position>=data.size())
                return 0;
            return data[position++];
        }
        char peek()
        {
            if(position>=data.size())
                return 0;
            else return data[position];
        }
        void reset(int p = 0)
        {
            position = p;
        }
        void skipSpace()
        {
            while(std::isspace(data[position]))
                position++;
        }
        std::string range(int start, int end) // end as in iterators
        {
            std::string result;
            for(int i = start; i < end && i < data.size(); ++i)
                result += data[i];
            return result;
        }
    private:
        std::vector<char> data;
        int position;
        
    };
}
#endif