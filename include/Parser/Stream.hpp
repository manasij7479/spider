#ifndef SPIDER_PARSER_STREAM_HPP
#define SPIDER_PARSER_STREAM_HPP
#include <vector>
#include <map>
#include <istream>
#include <cctype>
namespace dot
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
                in.read(&data[0], inSize);
            }
            position = 0;
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
        int remember()
        {
            int result = bookmarks.size();
            bookmarks[result]=position;
            return result;
        }
        void reset(int p)
        {
            position = bookmarks[p];
        }
        void skipSpace()
        {
            while(std::isspace(data[position]))
                position++;
        }
    private:
        std::vector<char> data;
        int position;
        std::map<int,int> bookmarks;
        
    };
}
#endif