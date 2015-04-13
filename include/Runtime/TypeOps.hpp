#ifndef SPIDER_TYPE_OPS_HPP
#define SPIDER_TYPE_OPS_HPP
#include "Runtime/Type.hpp"
#include "Runtime/GraphValue.hpp"
#include "Runtime/WindowValue.hpp"
#include "Runtime/ListValue.hpp"
#include "Runtime/FunctionValue.hpp"
#include <algorithm>
namespace spider
{
	/**
	 * \brief - to check for type mismatch.
	 * 
	 * Whether type of x is equal to t.
	 * 
	 * @param Value* x - First Parameter, a value whose type is to be checked
	 * 
	 * @param Vtype t - Second Parameter, expected type
	 * **/
    inline void assert_type(Value* x, VType t)
    {
        if ( t != VType::Any && x->type != t)
            throw std::runtime_error("Type Mismatch: Expected: '"+Value::TypeToNameMap()[t]+"'. Got: '"+Value::TypeToNameMap()[x->type]+"' \n");
    }
    /**
     * \brief - to check for size mismatch.
     * 
     * Whether number of elements in "args" is equal to "size".
     * 
     * @param std::vector<T> args - First Parameter, arguement list whose size is to be matched
     * 
     * @param uint size - Second Parameter, expected size
     * 
     * @param std::string reason  - Third Parameter, default value "<>"
     * **/
    template <typename T>
    void assert_size(std::vector<T> args, uint size, std::string reason = "<>")
    {
        if (args.size() != size)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }
    /**
     * \brief - to check for size mismatch.
     * 
     * @param std::vector<T> args - First Parameter, arguement list whose size is to be matched
     * 
     * @param std::function<bool(uint)> predicate - Second Parameter
     * 
     * @param std::string reason  - Third Parameter, default value "<>"
     * **/
    template <typename T>
    void assert_size(std::vector<T> args, std::function<bool(uint)> predicate, std::string reason = "<>")
    {
        if (predicate(args.size()) == false)
            throw std::runtime_error("Size Mismatch."+reason+"\n");
    }
    /**
    * \brief - function that returns a std::function. The returned function checks if a given number is greater than
    * int 'i'.
    * 
    * @param int i - Parameter, the number to be checked.
    * **/
    inline std::function<bool(uint)> greater(int i)
    {
        return [i](int x){return x > i;};
    }
    /**
    * \brief - function that returns a std::function. The returned function checks if a given number is lesser than
    * int 'i'.
    * 
    * @param int i - Parameter, the number to be checked.
    * **/
    inline std::function<bool(uint)> lesser(int i)
    {
        return [i](int x){return x < i;};
    }
    /**
    * \brief - function that returns a std::function. The returned function checks if a given number is greater than or
    * equal to int 'i'.
    * 
    * @param int i - Parameter, the number to be checked.
    * **/
    inline std::function<bool(uint)> greater_eq(int i)
    {
        return [i](int x){return x >= i;};
    }
    /**
    * \brief - function that returns a std::function. The returned function checks if a given number is lesser than or
    * equal to int 'i'.
    * 
    * @param int i - Parameter, the number to be checked.
    * **/
    inline std::function<bool(uint)> lesser_eq(int i)
    {
        return [i](int x){return x <= i;};
    }
    
    /**
     * \brief - returns graph from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns GraphValue*
     * **/
    inline GraphValue* getg(Value* v)
    {
        return static_cast<GraphValue*>(v);
    }
    /**
     * \brief - returns String from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns StringValue*
     * **/
    inline StringValue* gets(Value* v)
    {
        return static_cast<StringValue*>(v);
    }
    /**
     * \brief - returns integer from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns IntegerValue*
     * **/
    inline IntegerValue* geti(Value* v)
    {
        return static_cast<IntegerValue*>(v);
    }
    /**
     * \brief - returns bool from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns BoolValue*
     * **/
    inline BoolValue* getb(Value* v)
    {
        return static_cast<BoolValue*>(v);
    }
    /**
     * \brief - returns Window from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns WindowValue*
     * **/
    inline WindowValue* getw(Value* v)
    {
        return static_cast<WindowValue*>(v);
    }
	/**
     * \brief - returns float from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns FloatValue*
     * **/
    inline FloatValue* getf(Value* v)
    {
        return static_cast<FloatValue*>(v);
    }
    /**
     * \brief - returns list from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns ListValue*
     * **/
    inline ListValue* getl(Value* v)
    {
        return static_cast<ListValue*>(v);
    }
    /**
     * \brief - returns Dictionary from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns DictValue*
     * **/
    inline DictValue* getd(Value* v)
    {
        return static_cast<DictValue*>(v);
    }
    /**
     * \brief - returns Vertex Attribute from Value
     * 
     * @param Value *v - Parameter
     * 
     * @returns VattrValue*
     * **/
    inline VattrValue* getv(Value* v)
    {
        return static_cast<VattrValue*>(v);
    }
        inline FunctionValue* getfn(Value* v)
    {
        return static_cast<FunctionValue*>(v);
    }

    /**
     * \brief - function to throw an error message in case a type T is encountered which cannot be converted
     * to data types supported by SPIDER compiler.
     * 
     * @param T t - Parameter, data of an unknown data type T
     * **/
    template <typename T>
    inline Value* convertToValue(T t)
    {
        throw std::runtime_error("Can not convert '" + std::string(typeid(T).name()) + "' to Value.\n");
    }
    /**
     * \brief - to return values of types that are supported by SPIDER compiler and needs no conversion.
     * 
     * @param Value* data - Parameter, a value
     * 
     * @returns Value* - Value for data
     * **/
    template <>
    inline Value* convertToValue<Value*>(Value* data)
    {
        return data;
    }
    /**
     * \brief - converts any integer to IntegerValue
     * 
     * @param int data - Parameter, an integer value
     * 
     * @returns Value* - IntegerValue for data
     * **/
    template <>
    inline Value* convertToValue<int>(int data)
    {
        return new IntegerValue(data);
    }
    /**
     * \brief - converts any float to FloatValue
     * 
     * @param float data - Parameter, a float value
     * 
     * @returns Value* - FloatValue for data
     * **/
    template <>
    inline Value* convertToValue<float>(float data)
    {
        return new FloatValue(data);
    }
    /**
     * \brief - converts any boolean to BoolValue
     * 
     * @param bool data - Parameter, a boolean value
     * 
     * @returns Value* - BoolValue for data
     * **/
    template <>
    inline Value* convertToValue<bool>(bool data)
    {
        return new BoolValue(data);
    }
    /**
     * \brief - converts any string to StringValue
     * 
     * @param std::string data - Parameter, a string value
     * 
     * @returns Value* - StringValue for data
     * **/
    template <>
    inline Value* convertToValue<std::string>(std::string data)
    {
        return new StringValue(data);
    }
    /**
     * \brief - converts any std::vector<T> to std::vector<Value*>
     * 
     * @param const std::vector<T>& data - Parameter, a const std::vector<T>
     * 
     * @returns std::vector<Value*> - std::vector<Value*> for data
     * **/
    template <typename T>
    inline std::vector<Value*> convertToCompoundValue(const std::vector<T>& data)
    {
        std::vector<Value*> result(data.size());
        std::transform(data.begin(), data.end(), result.begin(), 
                    [](T x){return convertToValue(x);});
        return result;
    }
     /**
     * \brief - converts any std::map<K, Value*> to std::vector<Value*>
     * 
     * @param const std::map<K, T>& data - Parameter, a std::map<K, T>& data
     * 
     * @returns std::map<K, Value*> - std::map<K, Value*> for data
     * **/
    template <typename K , typename T>
    inline std::map<K, Value*> convertToCompoundValue(const std::map<K, T>& data)
    {
        std::map<K, Value*> result;
        for(auto p : data)
            result.insert({p.first, convertToValue(p.second)});
        return result;
    }
    /**
     * \brief - converts any std::vector<T> to ListValue
     * 
     * @param std::vector<T> data - Parameter, a std::vector<T> value
     * 
     * @returns Value* - ListValue for data
     * **/
    template <typename T>
    inline Value* convertToValue(std::vector<T> data)
    {
        return new ListValue(convertToCompoundValue(data));
    }
    /**
     * \brief - converts any const std::map<std::string, T>& to DictValue
     * 
     * @param const std::map<std::string, T>& data - Parameter, a const std::map<std::string, T>& value
     * 
     * @returns Value* - DictValue for data
     * **/
    template <typename T>
    inline Value* convertToValue(const std::map<std::string, T>& data)
    {
        return new DictValue(convertToCompoundValue(data));
    }
    /**
     * \brief - converts any const std::map<int, T>& to VattrValue
     * 
     * @param const std::map<int, T>& data - Parameter, a const std::map<int, T>& value
     * 
     * @returns Value* - VattrValue for data
     * **/
    template <typename T>
    inline Value* convertToValue(const std::map<int, T>& data)
    {
        return new VattrValue(convertToCompoundValue(data));
    }
    
    
    
}
#endif
