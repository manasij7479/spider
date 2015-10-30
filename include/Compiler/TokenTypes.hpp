#ifndef TOKEN_TYPES_HPP
#define TOKEN_TYPES_HPP
#include <string>
namespace spider
{
    class Token
    {
    public:
        enum class Type 
        {
            IntLiteral,
            StringLiteral,
            SpecialLiteral,
            FloatLiteral,
            Identifier,
            Symbol,
            Eof
        };
        Token(Type t, int l):type(t), line(l){}

        Type type;
        int line;
    };
    typedef Token::Type TType;
    
    class IntLiteralToken : public Token
    {
    public:
        IntLiteralToken(int n, int l):Token(TType::IntLiteral, l), data(n){}
        int data;
    };
    class FloatLiteralToken : public Token
    {
    public:
        FloatLiteralToken(float f, int l):Token(TType::FloatLiteral, l), data(f){}
        float data;
    };
    class StringLiteralToken : public Token
    {
    public:
        StringLiteralToken(std::string s, int l):Token(TType::StringLiteral, l), data(s){}
        std::string data;
    };
    class SpecialLiteralToken : public Token
    {
    public:
        SpecialLiteralToken(std::string s, int l):Token(TType::SpecialLiteral, l), data(s){}
        std::string data;
    };

    class SymbolToken : public Token
    {
    public:
        SymbolToken(std::string s, int l):Token(TType::Symbol, l), data(s){}
        std::string data;
        //TODO: classify during construction
    };

    class IdentifierToken : public Token
    {
    public:
        IdentifierToken(std::string s, int l): Token(TType::Identifier, l), data(s){}
        std::string data;
    };
    
    
    class EOFToken : public Token
    {
    public:
        EOFToken():Token(TType::Eof, -1){};
    };
    
    inline SymbolToken* getsy(Token* t)
    {
        return static_cast<SymbolToken*>(t);
    }
    inline IntLiteralToken* getil(Token* t)
    {
        return static_cast<IntLiteralToken*>(t);
    }
    inline FloatLiteralToken* getfl(Token* t)
    {
        return static_cast<FloatLiteralToken*>(t);
    }
    inline StringLiteralToken* getsl(Token* t)
    {
        return static_cast<StringLiteralToken*>(t);
    }
    inline IdentifierToken* getifr(Token* t)
    {
        return static_cast<IdentifierToken*>(t);
    }
    inline SpecialLiteralToken* getspc(Token* t)
    {
        return static_cast<SpecialLiteralToken*>(t);
    }
    
    
}
#endif